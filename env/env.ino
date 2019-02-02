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
#ifdef ARDUINO_ARCH_AVR
    SPCR &= ~_BV(SPE);  // releases PIN13
#endif
    pinMode(13, OUTPUT);
    //digitalWrite(13, 1);
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

void ceu_arduino_warn (int cnd, int err) {
    if (cnd) return;

    noInterrupts();
#ifdef ARDUINO_ARCH_AVR
    //SPCR &= ~_BV(SPE);  // releases PIN13
#endif
    pinMode(13, OUTPUT);
    //digitalWrite(13, 1);
    //for (;;) {
        for (int j=0; j<err; j++) {
            _DELAY(200);
            digitalWrite(13, 0);
            _DELAY(200);
            digitalWrite(13, 1);
        }
        _DELAY(500);
    //}
    digitalWrite(13, 0);
    interrupts();
}

#define ceu_callback_stop(trace)
#define ceu_callback_step(trace)
#define ceu_callback_async_pending(trace)
#define ceu_callback_wclock_dt(trace) ceu_arduino_callback_wclock_dt()
s32 ceu_arduino_callback_wclock_dt (void);
#define ceu_callback_wclock_min(dt,trace) ceu_arduino_callback_wclock_min(dt)
void ceu_arduino_callback_wclock_min (s32);
#define ceu_callback_abort(err,trace) ceu_arduino_callback_abort(err)
void ceu_arduino_callback_abort (int err);
#define ceu_callback_start(trace)
#define ceu_callback_isr_enable(on,trace) ceu_arduino_callback_isr_enable(on)
void ceu_arduino_callback_isr_enable (int on);
#define ceu_callback_isr_emit(n,evt,trace) ceu_arduino_callback_isr_emit(n,evt)
void ceu_arduino_callback_isr_emit (int n, void* evt);

#include "_ceu_app.c.h"

#ifdef CEU_PM

#ifndef CEU_PM_IMPL
#error Missing architecture implementation for power management.
#endif

#ifndef __WCLOCK_CEU__
//#error "Missing WCLOCK driver!"
s32 ceu_arduino_callback_wclock_dt (void) { return CEU_WCLOCK_INACTIVE; }
void ceu_arduino_callback_wclock_min (s32) {}
#endif

#else

u32 ceu_arduino_millis_old;
void ceu_arduino_callback_wclock_min (s32) {}
s32 ceu_arduino_callback_wclock_dt (void) {
    u32 now = TV.millis();
    u32 dt  = (now - ceu_arduino_millis_old);  // no problems with overflow
    ceu_arduino_millis_old = now;
    return dt*1000;
}

#endif

static tceu_nevt ceu_isrs[CEU_ISRS_N];

void ceu_arduino_callback_isr_enable (int on) {
    if (on) {
        interrupts();
    } else {
        noInterrupts();
    }
}

void ceu_arduino_callback_isr_emit (int n, void* evt) {
    ceu_isrs[n] = ((tceu_isr_evt*)evt)->id;
}

void setup () {
    memset(ceu_isrs, CEU_INPUT__NONE, sizeof(tceu_nevt)*CEU_ISRS_N);
#ifdef CEU_PM
    ceu_pm_init();
#else
    ceu_arduino_millis_old = TV.millis();
#endif
    ceu_start(0, NULL);

    while (1)
    {
        noInterrupts();
        for (int i=0; i<CEU_ISRS_N; i++) {
            tceu_nevt evt = ceu_isrs[i];
            if (evt != CEU_INPUT__NONE) {
                ceu_isrs[i] = CEU_INPUT__NONE;
                interrupts();
                ceu_input(evt, NULL);
                goto _CEU_ARDUINO_AWAKE_;
            }
        }
        interrupts();
#ifdef CEU_PM
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
#else
        ceu_input(CEU_INPUT__ASYNC, NULL);
#endif
_CEU_ARDUINO_AWAKE_:;
    }
}

void loop () {}
