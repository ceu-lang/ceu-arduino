#include "_ceu_app.c.h"

static int is_terminating = 0;
static int has_async      = 0;
static u32 old;

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
        default:
            ret.is_handled = 0;
    }
    return ret;
}

void setup () {
    old = millis();
    ceu_start();
}

void loop () {
    while (!is_terminating) {
        if (has_async) {
            has_async = 0;
            ceu_input(CEU_INPUT__ASYNC, NULL);
        }
        {
            u32 now = micros();
            s32 dt = now - old;     // no problems with overflow
            ceu_input(CEU_INPUT__WCLOCK, &dt);
            old = now;
        }
    }
    ceu_stop();
    while (1);
}

