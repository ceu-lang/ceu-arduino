#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* ser = ceu_sys_load((void*)0x3000);
    tceu_app* tst = ceu_sys_load((void*)0xD000);

    ceu_sys_link( tst,1  ,  ser,CEU_IN-1 );
    ceu_sys_link( tst,2  ,  ser,CEU_IN-2 );
    ceu_sys_link( tst,3  ,  ser,CEU_IN-3 );
    ceu_sys_link( tst,4  ,  ser,CEU_IN-4 );
    ceu_sys_link( ser,1  ,  tst,CEU_IN-1 );

    ceu_sys_start(ser);
    ceu_sys_start(tst);
}
