#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* ser = ceu_sys_start((void*)0x6000);
    tceu_app* tst = ceu_sys_start((void*)0x7000);

    ceu_sys_link( tst,1  ,  ser,244 );
    ceu_sys_link( tst,2  ,  ser,243 );
    ceu_sys_link( tst,3  ,  ser,242 );
    ceu_sys_link( tst,4  ,  ser,241 );
    ceu_sys_link( ser,1  ,  tst,240 );
}
