#define ceu_callback_assert_msg_ex(v,msg,file,line)                              \
    if (!(v)) {                                                                  \
        ceu_callback_num_ptr(CEU_CALLBACK_ABORT, 0, NULL);                       \
    }

#include "_ceu_app.c.h"

#ifdef CEU_FEATURES_ISR
#include "wiring_private.h"
#ifdef __AVR
#include <avr/interrupt.h>
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
    old = millis();
    //Serial.begin(9600);
    ceu_start();
}

void loop ()
{
    while (!is_terminating)
    {
        noInterrupts();

        /* ASYNC */
        if (has_async) {
            has_async = 0;
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }

#if !defined(CEU_ARDUINO_POLL_WCLOCK) || CEU_ARDUINO_POLL_WCLOCK!=0
        /* WCLOCK */
        {
            u32 now = micros();
            s32 dt = now - old;     // no problems with overflow
            ceu_input(CEU_INPUT__WCLOCK, &dt);
            old = now;
        }
#endif

        /* PINS */
        #include "pins_inputs.c.h"

        interrupts();
    }
    ceu_stop();
    while (1);
}

