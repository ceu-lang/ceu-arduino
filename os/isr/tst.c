#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* tst = ceu_sys_load((void*)0x9000);
    ceu_sys_start(tst);
    // TODO: check tst
}
