#define ceu_callback_assert_msg_ex(v,msg,file,line)                              \
    if (!(v)) {                                                                  \
        ceu_callback_num_ptr(CEU_CALLBACK_ABORT, 0, NULL);                       \
    }

#include "_ceu_app.c.h"

#ifndef CEU_ARDUINO_POLL_WCLOCK
    #ifdef CEU_ARDUINO_SLEEP
        #define CEU_ARDUINO_POLL_WCLOCK 0
    #else
        #define CEU_ARDUINO_POLL_WCLOCK 1
    #endif
#endif

#ifndef CEU_ARDUINO_POLL_PINS
    #ifdef CEU_ARDUINO_SLEEP
        #define CEU_ARDUINO_POLL_PINS 0
    #else
        #define CEU_ARDUINO_POLL_PINS 1
    #endif
#endif

#ifndef CEU_ARDUINO_SLEEP
#define CEU_ARDUINO_SLEEP 0
#endif

#if CEU_ARDUINO_SLEEP
#if CEU_ARDUINO_POLL_WCLOCK || CEU_ARDUINO_POLL_PINS
#error "Invalid option!"
#endif
#endif

#ifdef CEU_FEATURES_ISR
#include "wiring_private.h"
#ifdef __AVR
#include <avr/interrupt.h>
#if CEU_ARDUINO_SLEEP
#include <avr/sleep.h>
#include <avr/power.h>
#endif
/*
 * ... Thus, normally interrupts will remain disabled inside the handler until
 *     the handler exits, ...
 * <http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html>
 */
#else
#error "Unsupported Platform!"
#endif

static volatile tceu_isr isrs[_VECTORS_SIZE];
#include "isrs.c.h"
#endif

static int is_terminating = 0;
static int has_async      = 0;
static u32 old;
static u32 pins_bits      = 0;

tceu_callback_ret ceu_callback (int cmd, tceu_callback_arg p1,
                                         tceu_callback_arg p2)
{
    tceu_callback_ret ret = { .is_handled=1 };

#ifdef ceu_callback_user
    ret = ceu_callback_user(cmd, p1, p2);
    if (ret.is_handled) {
        return ret;
    }
#endif

    switch (cmd) {
        case CEU_CALLBACK_ABORT: {
            noInterrupts();
            pinMode(13, OUTPUT);
            for (;;) {
                digitalWrite(13, !digitalRead(13));
                delayMicroseconds(10000);
                delayMicroseconds(10000);
                delayMicroseconds(10000);
                delayMicroseconds(10000);
                delayMicroseconds(10000);
            }
            interrupts();
        }

        case CEU_CALLBACK_TERMINATING:
            is_terminating = 1;
            break;
        case CEU_CALLBACK_ASYNC_PENDING:
            has_async = 1;
            break;

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
            if (args[0] < EXTERNAL_NUM_INTERRUPTS) {
                attachInterrupt(args[0], (void(*)())(isr->fun), args[1]);    /* TODO: no mem */
            } else {
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
#endif

        case CEU_CALLBACK_OUTPUT:
            switch (p1.num) {
                #include "pins_outputs.c.h"
            }
            break;
        default:
            ret.is_handled = 0;
    }
    return ret;
}

void setup () {
    #include "pins_modes.c.h"
    old = micros();
    //Serial.begin(9600);

#ifdef CEU_FEATURES_ISR

    memset((void*)&isrs, 0, sizeof(isrs));

#if CEU_ARDUINO_SLEEP
    set_sleep_mode(SLEEP_MODE_IDLE);
#if 0
    set_sleep_mode(SLEEP_MODE_ADC);
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    set_sleep_mode(SLEEP_MODE_STANDBY);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
#endif
    power_timer0_disable();     // disables "millis()" clock
#endif

#endif

    ceu_start();
}

void loop ()
{
    while (!is_terminating)
    {
        /* ASYNC */
        if (has_async) {
            has_async = 0;
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }

#if CEU_ARDUINO_POLL_WCLOCK
        /* WCLOCK */
        {
            u32 now = micros();
            s32 dt = now - old;     // no problems with overflow
            ceu_input(CEU_INPUT__WCLOCK, &dt);
            old = now;
        }
#endif

#if CEU_ARDUINO_POLL_PINS
        /* PINS */
        #include "pins_inputs.c.h"
#endif

#ifdef CEU_FEATURES_ISR
#if CEU_ARDUINO_SLEEP
        if (!has_async) {
            sleep_mode();
            pinMode(12, 1);
            digitalWrite(12, !digitalRead(12));
        }
#endif
        {
            int i;
            for (i=0; i<_VECTORS_SIZE; i++) {
                tceu_isr* isr = &isrs[i];
                if (isr->evt.id != CEU_INPUT__NONE) {
                    tceu_evt_id_params evt = isr->evt;
                    isr->evt.id = CEU_INPUT__NONE;
                    ceu_input(evt.id, evt.params);
                }
            }
        }
#endif
    }
    ceu_stop();
    while (1);
}

