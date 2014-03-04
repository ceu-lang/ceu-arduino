#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio = ceu_sys_load((void*)0x2000);
    tceu_app* tst  = ceu_sys_load((void*)0xE000);

    ceu_sys_link( tst,1  ,  gpio,244);
    ceu_sys_link( tst,2  ,  gpio,243);
    ceu_sys_link(gpio,1  ,   tst,242);

    ceu_sys_start(gpio);
    ceu_sys_start(tst);
}
