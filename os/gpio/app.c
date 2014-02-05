#include "ceu_os.h"

extern tceu_app drv;
extern tceu_app app;

tceu_lnk lnk1 = { &app,1 ,  &drv,246, NULL };
tceu_lnk lnk2 = { &app,2 ,  &drv,245, NULL };
tceu_lnk lnk3 = { &drv,1 ,  &app,244, NULL };

void MAIN (void) {
	ceu_sys_app(&drv);
	ceu_sys_app(&app);
	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);
}
