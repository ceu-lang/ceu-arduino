#include "ceu_os.h"

extern int TST_SIZE;
extern void tst_init (tceu_app* app);

char tst_data[300]; // = malloc(TST_SIZE);
tceu_app tst;

void MAIN (void) {
    tst.data = (tceu_org*) tst_data;
    tst.init = &tst_init;
    tst.sys_vec = CEU_SYS_VEC;
    ceu_sys_start(&tst);
}
