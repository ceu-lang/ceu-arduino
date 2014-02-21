#include "ceu_os.h"

void MAIN (void)
{
    u16 gpio = ceu_sys_start(0x4000);
    u16 tst  = ceu_sys_start(0x5000);

    ceu_sys_link( tst,1  ,  gpio,245);
    ceu_sys_link( tst,2  ,  gpio,244);
    ceu_sys_link(gpio,1  ,   tst,243);
}
