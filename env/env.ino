#include "types.h"

#define CEU_STACK_N 100
#if ARDUINO_ARCH_AVR
    #define CEU_STACK_MAX 1000
#elif ARDUINO_ARCH_SAMD
    #define CEU_STACK_MAX 1000
#else
    #error "Unsupported Platform!"
#endif
#undef CEU_STACK_MAX

#define CEU_ISRS_N 100

#define _DELAY(ms)                      \
    {                                   \
        int i;                          \
        for (i=0; i<ms; i++) {          \
            delayMicroseconds(1000);    \
        }                               \
    }

#ifdef CEU_FEATURES_ISR
    #ifdef CEU_FEATURES_ISR_SLEEP
        #include "pm.c.h"
    #else
        // Set SLEEP always.
        // Currently, if ISR is set, but not ISR_SLEEP, the timer will not work well
        // because `ceu_timer_request` is called every tick and intermediary ticks are
        // lost due to prescaling.
        #error "Invalid option!"
    #endif
#endif

/* CALLBACKS */

#define ceu_callback_stop(trace)
#define ceu_callback_step(trace)
#define ceu_callback_wclock_dt(trace) ceu_arduino_callback_wclock_dt()
s32 ceu_arduino_callback_wclock_dt (void);
#define ceu_callback_wclock_min(dt,trace) ceu_arduino_callback_wclock_min(dt)
void ceu_arduino_callback_wclock_min (s32);
#define ceu_callback_abort(err,trace) ceu_arduino_callback_abort(err)
void ceu_arduino_callback_abort (int err);

#ifdef CEU_FEATURES_ISR

#define ceu_callback_start(trace)
void ceu_arduino_callback_isr_enable (int on);
#define ceu_callback_isr_enable(on,trace) ceu_arduino_callback_isr_enable(err)
#define ceu_callback_isr_emit(idx,args,trace) ceu_arduino_callback_isr_emit(idx,args)
#ifdef CEU_FEATURES_ISR_STATIC
void ceu_arduino_callback_isr_emit (int idx, void* evt);
#else
void ceu_arduino_callback_isr_emit (int idx, void* args);
void ceu_arduino_callback_isr_attach (int on, void* isr, int* args);
#define ceu_callback_isr_attach(on,isr,args,trace) ceu_arduino_callback_isr_attach(on,isr,args)
#endif

#else

#define ceu_callback_start(trace) ceu_arduino_callback_start()
void ceu_arduino_callback_start (void);

#endif

#define ceu_arduino_assert(cnd,err) if (!(cnd)) { ceu_arduino_callback_abort(err); }

#include "X_pins_outputs.c.h"

//#define ceu_assert_ex(a,b,c) // no assert
#define ceu_assert_ex(a,b,c) if (!(a)) { ceu_callback_abort((10+__COUNTER__),c); }
#define ceu_assert_sys(a,b)  if (!(a)) { ceu_callback_abort((10+__COUNTER__),CEU_TRACE_null); }

/* PROGRAM */

#include "_ceu_app.c.h"

#ifdef CEU_FEATURES_ISR

#ifdef CEU_FEATURES_ISR_DYNAMIC
    static tceu_isr isrs[_VECTOR_SIZE];
    #include "isrs.c.h"
#else
    static byte  isrs_buf[CEU_ISRS_N];
    static usize isrs_i = 0;
    static usize isrs_n = 0;
#endif

    void ceu_arduino_callback_isr_enable (int on) {
        if (on) {
            interrupts();
        } else {
            noInterrupts();
        }
    }

#ifdef CEU_FEATURES_ISR_DYNAMIC
    void ceu_arduino_callback_isr_attach (int on, void* isr, int* args) {
        if (on) {
            tceu_isr* isr_ = (tceu_isr*) isr;
#if 1
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                attachInterrupt(args[0], (void(*)())(isr_->fun), args[1]);    /* TODO: no mem */
            } else
#endif
            {
                isrs[args[0]] = *isr_;
            }
        } else {
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                detachInterrupt(args[0]);
            } else {
                isrs[args[0]].fun = NULL;
            }
        }
    }
#endif

#ifdef CEU_FEATURES_ISR_STATIC
    void ceu_arduino_callback_isr_emit (int idx, void* evt) {
        tceu_isr_evt* evt_ = (tceu_isr_evt*) evt;
        ceu_assert(isrs_n+sizeof(tceu_nevt)+sizeof(u8)+evt_->len < CEU_ISRS_N, "isrs buffer is full");

        *((tceu_nevt*)&isrs_buf[isrs_n]) = evt_->id;
        isrs_n += sizeof(tceu_nevt);
        *((u8*)&isrs_buf[isrs_n]) = evt_->len;
        isrs_n += sizeof(u8);
        memcpy(&isrs_buf[isrs_n], evt_->args, evt_->len);
    }
#else
    void ceu_arduino_callback_isr_emit (int idx, void* args) {
        //ceu_dbg_assert(isrs[p1.num].evt.id == CEU_INPUT__NONE);
        isrs[idx].evt = *((tceu_evt_id_params*)args);
    }
#endif

#else
    #ifdef CEU_FEATURES_ISR_SLEEP
        #error "Invalid option!"
    #endif
    #ifndef CEU_ARDUINO_SERIAL_SPEED
        #define CEU_ARDUINO_SERIAL_SPEED 9600
    #endif
#endif

#ifndef CEU_FEATURES_ISR
typedef struct tceu_arduino {
    u32 old;
    u32 pins_bits;
} tceu_arduino;

static tceu_arduino CEU_ARDUINO;

void ceu_arduino_callback_start (void) {
    CEU_ARDUINO.old       = micros();
    CEU_ARDUINO.pins_bits = 0;
}

void ceu_arduino_callback_wclock_min (s32 dt) {}

s32 ceu_arduino_callback_wclock_dt (void) {
    u32 now = micros();
    u32 dt  = (now - CEU_ARDUINO.old);  // no problems with overflow
    CEU_ARDUINO.old = now;
    return dt;
}
#endif

void ceu_arduino_callback_abort (int err) {
    noInterrupts();
    SPCR &= ~_BV(SPE);  // releases PIN13
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
    for (;;) {
        for (int j=0; j<err; j++) {
            _DELAY(200);
            digitalWrite(13, 0);
            _DELAY(200);
            digitalWrite(13, 1);
        }
        _DELAY(1000);
    }
    interrupts();
}

#if 0
static int ceu_callback_arduino (int cmd, tceu_callback_val p1, tceu_callback_val p2)
{
    int is_handled = 1;

    switch (cmd) {
        case CEU_CALLBACK_OUTPUT:
            switch (p1.num) {
                #include "pins_outputs.c.h"
                default:
                    is_handled = 0;
            }
            break;

        default:
            is_handled = 0;
    }
    return is_handled;
}
#endif

void setup () {
    #include "pins_modes.c.h"

#ifdef _CEU_INPUT_SERIAL_RECEIVE_BYTE_
    Serial.begin(CEU_ARDUINO_SERIAL_SPEED);
#endif

#ifdef CEU_FEATURES_ISR_DYNAMIC
    memset((void*)&isrs, 0, sizeof(isrs));
#endif

    //tceu_callback cb = { &ceu_callback_arduino, NULL };
#ifdef CEU_FEATURES_ISR_SLEEP
    ceu_pm_init();
#endif
    //ceu_start(&cb, 0, NULL);
    ceu_start(NULL, 0, NULL);

    while (1)
    {
#ifdef CEU_FEATURES_ISR
        {
            noInterrupts();
#ifdef CEU_FEATURES_ISR_STATIC
            if (isrs_i < isrs_n) {
                tceu_nevt id = *((tceu_nevt*)&isrs_buf[isrs_i]);
                isrs_i += sizeof(tceu_nevt);
                u8 len = *((u8*)&isrs_buf[isrs_i]);
                isrs_i += sizeof(u8);
                void* args = &isrs_buf[isrs_i];
                isrs_i += len;
                interrupts();
                ceu_input(id, args);
                goto _CEU_ARDUINO_AWAKE_;
            } else {
                isrs_i = isrs_n = 0;
            }
#else
            for (int i=0; i<_VECTOR_SIZE; i++) {
                tceu_isr* isr = &isrs[i];
                if (isr->evt.id != CEU_INPUT__NONE) {
                    tceu_evt_id_params evt = isr->evt;
                    isr->evt.id = CEU_INPUT__NONE;
                    interrupts();
                    ceu_input(evt.id, evt.params);
                    goto _CEU_ARDUINO_AWAKE_;
                }
            }
#endif
            interrupts();
#ifdef CEU_FEATURES_ISR_SLEEP
#ifdef CEU_FEATURES_ASYNC
            if (!CEU_APP.async_pending)
#endif
            {
                ceu_pm_sleep();
            }
#ifdef CEU_FEATURES_ASYNC
            else
#endif
#endif
            {
#ifdef CEU_FEATURES_ASYNC
                ceu_input(CEU_INPUT__ASYNC, NULL);
#endif
            }
_CEU_ARDUINO_AWAKE_:;
        }

#else // !CEU_FEATURES_ISR

#ifdef CEU_FEATURES_ASYNC
        ceu_input(CEU_INPUT__ASYNC, NULL);
#endif
        #include "pins_inputs.c.h"
#ifdef _CEU_INPUT_SERIAL_RECEIVE_BYTE_
        if (Serial.available()) {
            byte c = Serial.read();
            ceu_input(CEU_INPUT_SERIAL_RECEIVE_BYTE, &c);
        }
#endif

#endif
    }
}

void loop () {}
