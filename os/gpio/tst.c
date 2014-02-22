#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio = ceu_sys_start((void*)0x4000);
    tceu_app* tst  = ceu_sys_start((void*)0x5000);

    ceu_sys_link( tst,1  ,  gpio,245);
    ceu_sys_link( tst,2  ,  gpio,244);
    ceu_sys_link(gpio,1  ,   tst,243);
}
