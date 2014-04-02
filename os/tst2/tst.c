#include "ceu_os.h"

// TODO: tst.ceu (shell)

void MAIN (void)
{
    tceu_app* gpio = ceu_sys_load((void*)0x2000);
    tceu_app* app1 = ceu_sys_load((void*)0x3000);
    tceu_app* app2 = ceu_sys_load((void*)0x4800);

    ceu_sys_link(app1,1  ,  gpio,CEU_IN-1);
    ceu_sys_link(app1,2  ,  gpio,CEU_IN-2);
    ceu_sys_link(app2,1  ,  gpio,CEU_IN-1);
    ceu_sys_link(app2,2  ,  gpio,CEU_IN-2);

    ceu_sys_start(gpio);
    ceu_sys_start(app1);
    ceu_sys_start(app2);
}
