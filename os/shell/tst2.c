#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* serial = ceu_sys_load((void*)0x3000);
    tceu_app* shell  = ceu_sys_load((void*)0x4000);
    tceu_app* s2s    = ceu_sys_load((void*)0x6000);

    ceu_sys_link(s2s,1    ,  shell,244);    // COMMAND

    ceu_sys_link(s2s,2    ,  serial,244);   // BEGIN
    ceu_sys_link(s2s,3    ,  serial,243);   // END
    ceu_sys_link(s2s,4    ,  serial,241);   // WRITE_BUF

    ceu_sys_link(serial,1 ,  s2s,240);      // READ

    ceu_sys_start(serial);
    ceu_sys_start(shell);
    ceu_sys_start(s2s);
}

