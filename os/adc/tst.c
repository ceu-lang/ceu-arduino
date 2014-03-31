#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio = ceu_sys_load((void*)0x2000);
    tceu_app* adc  = ceu_sys_load((void*)0x7000);
    tceu_app* tst  = ceu_sys_load((void*)0x8000);

    // GPIO
    ceu_sys_link( tst,1  ,  gpio,CEU_IN-1);
    ceu_sys_link( tst,2  ,  gpio,CEU_IN-2);

    // ADC
    ceu_sys_link(tst,3  ,  adc,CEU_IN-1);
    ceu_sys_link(tst,4  ,  adc,CEU_IN-2);
    ceu_sys_link(adc,1  ,  tst,CEU_IN-1);

    ceu_sys_start(gpio);
    ceu_sys_start(adc);
    ceu_sys_start(tst);
}
