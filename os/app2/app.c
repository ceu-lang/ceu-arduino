#include "ceu_os.h"

extern tceu_app gpio;
extern tceu_app app1;
extern tceu_app app2;
extern tceu_app shell;

tceu_lnk lnk1 = { &app1,1   ,  &gpio,245, NULL };
tceu_lnk lnk2 = { &app1,2   ,  &gpio,244, NULL };
tceu_lnk lnk3 = { &app2,1   ,  &gpio,245, NULL };
tceu_lnk lnk4 = { &app2,2   ,  &gpio,244, NULL };

void MAIN (void) {
	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);
	ceu_sys_link(&lnk4);
	ceu_sys_start(&gpio);
	ceu_sys_start(&shell);
}
