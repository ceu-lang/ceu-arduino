#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* gpio = ceu_sys_start((void*)0x4000);
    tceu_app* app1 = ceu_sys_start((void*)0x2000);
    tceu_app* app2 = ceu_sys_start((void*)0x2800);

    ceu_sys_link(app1,1  ,  gpio,244);
    ceu_sys_link(app1,2  ,  gpio,243);
    ceu_sys_link(app2,1  ,  gpio,244);
    ceu_sys_link(app2,2  ,  gpio,243);
}
