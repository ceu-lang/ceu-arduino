#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio       = ceu_sys_load((void*)0x4000);
    tceu_app* gpio_tst   = ceu_sys_load((void*)0x5000);

    ceu_sys_link(gpio_tst,1   ,   gpio,    244);
    ceu_sys_link(gpio_tst,2   ,   gpio,    243);
    ceu_sys_link(gpio,    1   ,   gpio_tst,242);

    tceu_app* serial     = ceu_sys_load((void*)0x6000);
    tceu_app* serial_tst = ceu_sys_load((void*)0x7000);

    ceu_sys_link( serial_tst,1   ,   serial,    244 );
    ceu_sys_link( serial_tst,2   ,   serial,    243 );
    ceu_sys_link( serial_tst,3   ,   serial,    242 );
    ceu_sys_link( serial_tst,4   ,   serial,    241 );
    ceu_sys_link( serial,    1   ,   serial_tst,240 );

    ceu_sys_start(gpio);
    ceu_sys_start(gpio_tst);
    ceu_sys_start(serial);
    ceu_sys_start(serial_tst);
}
