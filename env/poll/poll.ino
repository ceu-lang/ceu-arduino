#include "_ceu_app.c.h"

static int is_terminating = 0;
static int has_async      = 0;
static u32 old;
static u32 pins_bits;

tceu_callback_ret ceu_callback (int cmd, tceu_callback_arg p1,
                                         tceu_callback_arg p2)
{
    tceu_callback_ret ret = { .is_handled=1 };
    switch (cmd) {
        case CEU_CALLBACK_TERMINATING:
            is_terminating = 1;
            break;
        case CEU_CALLBACK_ASYNC_PENDING:
            has_async = 1;
            break;
        case CEU_CALLBACK_OUTPUT:
            switch (p1.num) {
                case CEU_OUTPUT_PIN13:
                    digitalWrite(13, *((int*)p2.ptr));
                    break;
            }
            break;
        default:
            ret.is_handled = 0;
    }
    return ret;
}

void setup () {
#ifdef _CEU_INPUT_PIN13_
    pinMode(13, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN13_
    pinMode(13, OUTPUT);
#endif
#ifdef _CEU_INPUT_PIN02_
    pinMode( 2, INPUT);
#endif
#ifdef _CEU_OUTPUT_PIN02_
    pinMode( 2, OUTPUT);
#endif
    old = millis();
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

        /* WCLOCK */
        {
            u32 now = micros();
            s32 dt = now - old;     // no problems with overflow
            ceu_input(CEU_INPUT__WCLOCK, &dt);
            old = now;
        }

        /* PINS */
        {
#ifdef _CEU_INPUT_PIN02_
            int tmp = digitalRead(2);
            if (bitRead(pins_bits,2) != tmp) {
                bitWrite(pins_bits,2,tmp);
                ceu_input(CEU_INPUT_PIN02, &tmp);
            }
#endif
        }
    }
    ceu_stop();
    while (1);
}

