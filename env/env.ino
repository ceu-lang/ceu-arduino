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

#define CEU_ISRS_N 200

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
#define ceu_callback_isr_emit(evt,trace) ceu_arduino_callback_isr_emit(evt)
void ceu_arduino_callback_isr_emit (void* evt);

#include "_ceu_app.c.h"

#ifdef CEU_PM
#ifndef CEU_PM_IMPL
#error Missing architecture implementation for power management.
#endif
#endif

#ifndef __WCLOCK_CEU__
//#error "Missing WCLOCK driver!"
s32 ceu_arduino_callback_wclock_dt (void) { return CEU_WCLOCK_INACTIVE; }
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

void ceu_arduino_callback_isr_emit (void* evt) {
    tceu_isr_evt* evt_ = (tceu_isr_evt*) evt;
#ifdef ARDUINO_ARCH_SAMD
    if (evt_->len%4 != 0) {
        evt_->len += 4-(evt_->len%4); // TODO: prevents unaligned access to ceu_isrs_buf
    }
#endif

    int nxt = ceu_isrs_n + offsetof(tceu_isr_evt,args) + evt_->len;

    if (ceu_isrs_i <= ceu_isrs_n) {
        if (nxt+sizeof(tceu_nevt) > CEU_ISRS_N) {      // +sizeof(tceu_nevt) to fit NONE
            *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_n]) = CEU_INPUT__NONE;     // evt does not fit the end of the buffer
            ceu_isrs_n = 0;
            nxt = 0 + offsetof(tceu_isr_evt,args) + evt_->len;
        }
    }
    if (ceu_isrs_i > ceu_isrs_n) {     // test again b/c ceu_isrs_n may change above
        ceu_assert(nxt < ceu_isrs_i, "isrs buffer is full");
    }

    *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_n+offsetof(tceu_isr_evt,id )]) = evt_->id;
    *((u8*)       &ceu_isrs_buf[ceu_isrs_n+offsetof(tceu_isr_evt,len)]) = evt_->len;
    ceu_isrs_n += offsetof(tceu_isr_evt,args);

    memcpy(&ceu_isrs_buf[ceu_isrs_n], evt_->args, evt_->len);
    ceu_isrs_n += evt_->len;
}

void setup () {
#ifdef CEU_PM
    ceu_pm_init();
#endif
    ceu_start(0, NULL);

    while (1)
    {
        noInterrupts();
        if (ceu_isrs_i != ceu_isrs_n) {
            tceu_nevt id  = *((tceu_nevt*)&ceu_isrs_buf[ceu_isrs_i+offsetof(tceu_isr_evt,id )]);
            u8        len = *((u8*)       &ceu_isrs_buf[ceu_isrs_i+offsetof(tceu_isr_evt,len)]);
            ceu_isrs_i += offsetof(tceu_isr_evt,args);
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
