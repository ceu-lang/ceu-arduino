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

    // load 0 0xF000        // tst0
    // start 0
    // start 0

    // load 0 0x2000        // gpio
    // start 0

    // load 1 0xC000        // app1
    // link 1 1 0 244
    // link 1 2 0 243
    // start 1

    // load 2 0xC500
    // link 2 1 0 244
    // link 2 2 0 243
    // start 2

    // stop 1
    // stop 0
}

