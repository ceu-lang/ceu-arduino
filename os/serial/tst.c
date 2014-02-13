#include "ceu_os.h"

extern int SERIAL_SIZE;
extern void serial_init (tceu_app* app);

extern int TST_SIZE;
extern void tst_init (tceu_app* app);

char serial_data[300]; // TODO: = malloc(SERIAL_SIZE);
char tst_data[300]; // TODO: = malloc(TST_SIZE);

tceu_app serial;
tceu_app tst;

tceu_lnk lnk1 = { &tst,1 ,  &serial,245, NULL };
tceu_lnk lnk2 = { &tst,2 ,  &serial,244, NULL };
tceu_lnk lnk3 = { &tst,3 ,  &serial,243, NULL };
tceu_lnk lnk4 = { &serial,1 ,  &tst,242, NULL };

void MAIN (void) {
    serial.data = (tceu_org*) serial_data;
    serial.init = serial_init;
    serial.sys_vec = CEU_SYS_VEC;

    tst.data = (tceu_org*) tst_data;
    tst.init = tst_init;
    tst.sys_vec = CEU_SYS_VEC;

    ceu_sys_link(&lnk1);
    ceu_sys_link(&lnk2);
    ceu_sys_link(&lnk3);
    ceu_sys_link(&lnk4);

    ceu_sys_start(&serial);
    ceu_sys_start(&tst);
}
