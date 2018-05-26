#if 1
    #define ceu_assert_ex(a,b,c) if (!(a)) { ceu_callback_abort((10+__COUNTER__),c); }
    #define ceu_assert_sys(a,b)  if (!(a)) { ceu_callback_abort((10+__COUNTER__),CEU_TRACE_null); }
    #define ceu_arduino_assert(cnd,err) if (!(cnd)) { ceu_arduino_callback_abort(err); }
#else
    #define ceu_assert_ex(a,b,c)        // no assert
    #define ceu_assert_sys(a,b)         // no assert
    #define ceu_arduino_assert(cnd,err) // no assert
#endif

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

///////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT
///////////////////////////////////////////////////////////////////////////////

#include "types.h"

#define _DELAY(ms)                      \
    {                                   \
        int i;                          \
        for (i=0; i<ms; i++) {          \
            delayMicroseconds(1000);    \
        }                               \
    }

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

#define ceu_callback_stop(trace)
#define ceu_callback_step(trace)
#define ceu_callback_wclock_dt(trace) ceu_arduino_callback_wclock_dt()
s32 ceu_arduino_callback_wclock_dt (void);
#define ceu_callback_wclock_min(dt,trace) ceu_arduino_callback_wclock_min(dt)
void ceu_arduino_callback_wclock_min (s32);
#define ceu_callback_abort(err,trace) ceu_arduino_callback_abort(err)
void ceu_arduino_callback_abort (int err);
#define ceu_callback_start(trace)
#define ceu_callback_isr_enable(on,trace) ceu_arduino_callback_isr_enable(on)
void ceu_arduino_callback_isr_enable (int on);
#define ceu_callback_isr_emit(idx,args,trace) ceu_arduino_callback_isr_emit(idx,args)
void ceu_arduino_callback_isr_emit (int idx, void* evt);

#include "_ceu_app.c.h"

#ifndef __WCLOCK_CEU__
//#error "Missing WCLOCK driver!"
s32 ceu_arduino_callback_wclock_dt (void) { return 0; }
void ceu_arduino_callback_wclock_min (s32) {}
#endif

static byte  ceu_isrs_buf[CEU_ISRS_N];
static usize ceu_isrs_i = 0;
static usize ceu_isrs_n = 0;

void ceu_arduino_callback_isr_enable (int on) {
    if (on) {
        interrupts();
    } else {
        noInterrupts();
    }
}

void ceu_arduino_callback_isr_emit (int idx, void* evt) {
    tceu_isr_evt* evt_ = (tceu_isr_evt*) evt;

    int nxt = ceu_isrs_n+sizeof(tceu_nevt)+sizeof(u8)+evt_->len;
    if (ceu_isrs_i <= ceu_isrs_n) {
        if (nxt+sizeof(tceu_nevt) > CEU_ISRS_N) {      // +sizeof(tceu_nevt) to fit NONE
            *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_n]) = CEU_INPUT__NONE;     // evt does not fit the end of the buffer
            ceu_isrs_n = 0;
            nxt = sizeof(tceu_nevt)+sizeof(u8)+evt_->len;
        }
    }
    if (ceu_isrs_i > ceu_isrs_n) {     // test again b/c ceu_isrs_n may change above
        ceu_assert(nxt < ceu_isrs_i, "isrs buffer is full");
    }

    *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_n]) = evt_->id;
    ceu_isrs_n += sizeof(tceu_nevt);
    *((u8*)&ceu_isrs_buf[ceu_isrs_n]) = evt_->len;
    ceu_isrs_n += sizeof(u8);
    memcpy(&ceu_isrs_buf[ceu_isrs_n], evt_->args, evt_->len);
    ceu_isrs_n += evt_->len;
}

void setup () {
#ifdef CEU_PM
    ceu_pm_init();
#endif
    ceu_start(NULL, 0, NULL);

    while (1)
    {
        noInterrupts();
        if (ceu_isrs_i != ceu_isrs_n) {
            tceu_nevt id = *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_i]);
            ceu_isrs_i += sizeof(tceu_nevt);
            u8 len = *((u8*)&ceu_isrs_buf[ceu_isrs_i]);
            ceu_isrs_i += sizeof(u8);
            void* args = &ceu_isrs_buf[ceu_isrs_i];
            if (id == CEU_INPUT__NONE) {
                ceu_isrs_i = 0;
            } else {
                ceu_isrs_i += len;
            }
            interrupts();
            ceu_input(id, args);
            goto _CEU_ARDUINO_AWAKE_;
        }
        interrupts();
#ifdef CEU_FEATURES_ASYNC
        if (!CEU_APP.async_pending)
#endif
        {
            ceu_pm_sleep();
        }
#ifdef CEU_FEATURES_ASYNC
        else
#endif
        {
#ifdef CEU_FEATURES_ASYNC
            ceu_input(CEU_INPUT__ASYNC, NULL);
#endif
        }
_CEU_ARDUINO_AWAKE_:;
    }
}

void loop () {}
