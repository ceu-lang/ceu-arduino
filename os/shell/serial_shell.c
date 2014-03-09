#include "ceu_os.h"

void MAIN (void)
{
    tceu_app* serial = ceu_sys_load((void*)0x3000);
    tceu_app* shell  = ceu_sys_load((void*)0x4000);
    tceu_app* s2s    = ceu_sys_load((void*)0x5000);

    ceu_sys_link(s2s,1    ,  shell,CEU_IN-1);    // COMMAND

    ceu_sys_link(s2s,2    ,  serial,CEU_IN-1);   // BEGIN
    ceu_sys_link(s2s,3    ,  serial,CEU_IN-2);   // END
    ceu_sys_link(s2s,4    ,  serial,CEU_IN-3);   // WRITE
    ceu_sys_link(s2s,5    ,  serial,CEU_IN-4);   // WRITE_BUF

    ceu_sys_link(serial,1 ,  s2s,CEU_IN-1);      // READ

    ceu_sys_start(serial);
    ceu_sys_start(shell);
    ceu_sys_start(s2s);
}
