#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* shell = ceu_sys_load((void*)0x4000);
    tceu_app* tst   = ceu_sys_load((void*)0xA000);

    ceu_sys_link(tst,1  ,  shell,244);

    ceu_sys_start(shell);
    ceu_sys_start(tst);
}

