#include "ceu_os.h"

extern tceu_app drv;
extern tceu_app tst;

tceu_lnk lnk1 = { &tst,1 ,  &drv,245, NULL };
tceu_lnk lnk2 = { &tst,2 ,  &drv,244, NULL };
tceu_lnk lnk3 = { &drv,1 ,  &tst,243, NULL };

void MAIN (void) {
	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);
	ceu_sys_start(&drv);
	ceu_sys_start(&tst);
}
