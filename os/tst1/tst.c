#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio       = ceu_sys_load((void*)0x2000);
    tceu_app* gpio_tst   = ceu_sys_load((void*)0xE000);

    ceu_sys_link(gpio_tst,1   ,   gpio,    CEU_IN-1);
    ceu_sys_link(gpio_tst,2   ,   gpio,    CEU_IN-2);
    ceu_sys_link(gpio,    1   ,   gpio_tst,CEU_IN-1);

    tceu_app* serial     = ceu_sys_load((void*)0x3000);
    tceu_app* serial_tst = ceu_sys_load((void*)0xD000);

    ceu_sys_link( serial_tst,1   ,   serial,    CEU_IN-1 );
    ceu_sys_link( serial_tst,2   ,   serial,    CEU_IN-2 );
    ceu_sys_link( serial_tst,3   ,   serial,    CEU_IN-3 );
    ceu_sys_link( serial_tst,4   ,   serial,    CEU_IN-4 );
    ceu_sys_link( serial,    1   ,   serial_tst,CEU_IN-1 );

    ceu_sys_start(gpio);
    ceu_sys_start(gpio_tst);
    ceu_sys_start(serial);
    ceu_sys_start(serial_tst);
}
