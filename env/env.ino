#define CEU_ARDUINO_ASSERT          // numeric assert
//#define ceu_assert_ex(a,b,c)      // no assert

#if ARDUINO_ARCH_AVR
    #define CEU_STACK_MAX  200
#elif ARDUINO_ARCH_SAMD
    #define CEU_STACK_MAX 1000
#else
    #error "Unsupported Platform!"
#endif
//#undef CEU_STACK_MAX

#define _DELAY(ms)                      \
    {                                   \
        int i;                          \
        for (i=0; i<ms; i++) {          \
            delayMicroseconds(1000);    \
        }                               \
    }

#ifdef CEU_ARDUINO_ASSERT
#define ceu_assert_ex(a,b,c) if (a == 0) { ceu_arduino_halt((int)b); }
void ceu_arduino_halt (int v);
#endif

#ifdef CEU_FEATURES_ISR
    #ifdef CEU_FEATURES_ISR_SLEEP
        #include "types.h"
        #include "pm.c.h"
    #else
        // Set SLEEP always.
        // Currently, if ISR is set, but not ISR_SLEEP, the timer will not work well
        // because `ceu_timer_request` is called every tick and intermediary ticks are
        // lost due to prescaling.
        #error "Invalid option!"
    #endif
#endif

#include "_ceu_app.c.h"

#ifdef CEU_ARDUINO_ASSERT
void ceu_arduino_halt (int v) {
    if (v<1 || v>10) { v=1; }
    noInterrupts();
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
    for (;;) {
        for (int j=0; j<v; j++) {
            _DELAY(150);
            digitalWrite(13, 0);
            _DELAY(150);
            digitalWrite(13, 1);
        }
        _DELAY(1000);
    }
    interrupts();
}
#endif

#ifdef CEU_FEATURES_ISR
    #include "wiring_private.h"

    #ifndef _VECTOR_SIZE
        #ifdef _VECTORS_SIZE
            #define _VECTOR_SIZE (_VECTORS_SIZE/4)
        #elif ARDUINO_ARCH_SAMD
            #define _VECTOR_SIZE PERIPH_COUNT_IRQn
        #else
            #error "Unsupported Platform!"
        #endif
    #endif

    static tceu_isr isrs[_VECTOR_SIZE];
    #include "isrs.c.h"
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
#endif

static int ceu_callback_arduino (int cmd, tceu_callback_val p1, tceu_callback_val p2)
{
    int is_handled = 1;

    switch (cmd) {
        case CEU_CALLBACK_START:
#ifndef CEU_FEATURES_ISR
            CEU_ARDUINO.old       = micros();
            CEU_ARDUINO.pins_bits = 0;
#endif
            break;

        case CEU_CALLBACK_ABORT: {
            noInterrupts();
            pinMode(13, OUTPUT);
            for (;;) {
                digitalWrite(13, !digitalRead(13));
                for (int i=0; i<50; i++) {
                    delayMicroseconds(1000);    /* max is 16383 */
                }
            }
            interrupts();
        }

#if 0
        case CEU_CALLBACK_LOG: {
            switch (p1.num) {
                case 0:
                    Serial.print((char*)p2.ptr);
                    break;
                case 1:
                    Serial.print(p2.num,HEX);
                    break;
                case 2:
                    Serial.print(p2.num);
                    break;
            }
            break;
        }
#endif

#ifdef CEU_FEATURES_ISR
        case CEU_CALLBACK_ISR_ENABLE: {
            if (p1.num == 1) {
                interrupts();
            } else {
                noInterrupts();
            }
            break;
        }
        case CEU_CALLBACK_ISR_ATTACH: {
            tceu_isr* isr = (tceu_isr*) p1.ptr;
            int* args = (int*) p2.ptr;
            //if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                //attachInterrupt(args[0], (void(*)())(isr->fun), args[1]);    /* TODO: no mem */
            //} else
            {
                isrs[args[0]] = *isr;
            }
            break;
        }
        case CEU_CALLBACK_ISR_DETACH: {
            int* args = (int*)p2.ptr;
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                detachInterrupt(args[0]);
            } else {
                isrs[args[0]].fun = NULL;
            }
            break;
        }
        case CEU_CALLBACK_ISR_EMIT: {
            //ceu_dbg_assert(isrs[p1.num].evt.id == CEU_INPUT__NONE);
            isrs[p1.num].evt = *((tceu_evt_id_params*) p2.ptr);
            break;
        }
        case CEU_CALLBACK_WCLOCK_DT:
            ceu_callback_ret.num = CEU_WCLOCK_INACTIVE;
            break;
#else
        case CEU_CALLBACK_WCLOCK_DT:
            ceu_callback_ret.num = ceu_arduino_dt();
            break;
#endif

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

#ifndef CEU_FEATURES_ISR
s32 ceu_arduino_dt (void) {
    u32 now = micros();
    u32 dt  = (now - CEU_ARDUINO.old);  // no problems with overflow
    CEU_ARDUINO.old = now;
    return dt;
}
#endif

void setup () {
    #include "pins_modes.c.h"

#ifdef _CEU_INPUT_SERIAL_RECEIVE_BYTE_
    Serial.begin(CEU_ARDUINO_SERIAL_SPEED);
#endif

#ifdef CEU_FEATURES_ISR
    memset((void*)&isrs, 0, sizeof(isrs));
#endif

    tceu_callback cb = { &ceu_callback_arduino, NULL };
#ifdef CEU_FEATURES_ISR_SLEEP
    ceu_pm_init();
#endif
    ceu_start(&cb, 0, NULL);

    while (!CEU_APP.end_ok)
    {
#ifdef CEU_FEATURES_ISR
        {
            tceu_evt_id_params evt;
            int i;
            noInterrupts();
            for (i=0; i<_VECTOR_SIZE; i++) {
                tceu_isr* isr = &isrs[i];
                if (isr->evt.id != CEU_INPUT__NONE) {
                    evt = isr->evt;
                    isr->evt.id = CEU_INPUT__NONE;
                    interrupts();
                    ceu_input(evt.id, evt.params);
                    goto _CEU_ARDUINO_AWAKE_;
                }
            }
            interrupts();
#ifdef CEU_FEATURES_ISR_SLEEP
            if (!CEU_APP.async_pending) {
                ceu_pm_sleep();
            }
            else
#endif
            {
                ceu_input(CEU_INPUT__ASYNC, NULL);
            }
_CEU_ARDUINO_AWAKE_:;
        }

#else // !CEU_FEATURES_ISR

        ceu_input(CEU_INPUT__ASYNC, NULL);
        #include "pins_inputs.c.h"
#ifdef _CEU_INPUT_SERIAL_RECEIVE_BYTE_
        if (Serial.available()) {
            byte c = Serial.read();
            ceu_input(CEU_INPUT_SERIAL_RECEIVE_BYTE, &c);
        }
#endif

#endif
    }
    ceu_stop();
    ceu_assert_ex(0, 10, CEU_TRACE_null);
    while (1);
}

void loop () {}
