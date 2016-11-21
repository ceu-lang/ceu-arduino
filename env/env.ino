#define ceu_callback_assert_msg_ex(v,msg,file,line)                              \
    if (!(v)) {                                                                  \
        ceu_callback_num_ptr(CEU_CALLBACK_ABORT, 0, NULL);                       \
    }

#include "_ceu_app.c.h"

#ifdef CEU_FEATURES_ISR
    #include "wiring_private.h"
    #ifdef __AVR
        #include <avr/interrupt.h>
        #ifdef CEU_FEATURES_ISR_SLEEP
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
#else
    #ifdef CEU_FEATURES_ISR_SLEEP
        #error "Invalid option!"
    #endif
#endif

typedef struct tceu_arduino {
    int is_term;
    int has_async;
    u32 old;
    u32 pins_bits;
} tceu_arduino;

static tceu_arduino CEU_ARDUINO;

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
        case CEU_CALLBACK_START:
            CEU_ARDUINO.is_term   = 0;
            CEU_ARDUINO.has_async = 0;
#ifndef CEU_FEATURES_ISR
            CEU_ARDUINO.old       = micros();
#endif
            CEU_ARDUINO.pins_bits = 0;
            break;

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
            CEU_ARDUINO.is_term = 1;
            break;
        case CEU_CALLBACK_ASYNC_PENDING:
            CEU_ARDUINO.has_async = 1;
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
#else
        case CEU_CALLBACK_WCLOCK_DT: {
            u32 now = micros();
            s32 dt  = (u32)(now - CEU_ARDUINO.old);  // no problems with overflow
            CEU_ARDUINO.old = now;

            ret.value.num = dt;
            ret.is_handled = 1;
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

#ifdef CEU_FEATURES_ISR

    memset((void*)&isrs, 0, sizeof(isrs));

#ifdef CEU_FEATURES_ISR_SLEEP
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
    while (!CEU_ARDUINO.is_term)
    {
        /* ASYNC */
        if (CEU_ARDUINO.has_async) {
            CEU_ARDUINO.has_async = 0;
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }

#ifdef CEU_FEATURES_ISR
        {
            tceu_evt_id_params evt;
            int i;
            noInterrupts();
            for (i=0; i<_VECTORS_SIZE; i++) {
                tceu_isr* isr = &isrs[i];
                if (isr->evt.id != CEU_INPUT__NONE) {
                    evt = isr->evt;
                    isr->evt.id = CEU_INPUT__NONE;
                    interrupts();
                    //pinMode(12, 1);
                    //digitalWrite(12, !digitalRead(12));
                    ceu_input(evt.id, evt.params);
                    goto _CEU_ARDUINO_AWAKE_;
                }
            }
#ifdef CEU_FEATURES_ISR_SLEEP
            //sleep_mode();
            if (!CEU_ARDUINO.has_async) {
                sleep_enable();
                interrupts();
                sleep_cpu();
                sleep_disable();
            }
#endif
            interrupts();
_CEU_ARDUINO_AWAKE_:;
        }
#else // !CEU_FEATURES_ISR
        /* WCLOCK */
        {
            s32 dt = ceu_callback_void_void(CEU_CALLBACK_WCLOCK_DT).value.num;
            ceu_input(CEU_INPUT__WCLOCK, &dt);
        }
        /* PINS */
        #include "pins_inputs.c.h"
#endif

    }
    ceu_stop();
    ceu_dbg_assert(0);
    while (1);
}

