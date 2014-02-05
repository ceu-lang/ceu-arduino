#include "ceu_os.h"

extern tceu_app drv;
extern tceu_app app;

tceu_app* APPS = NULL;
tceu_lnk* LNKS = NULL;
tceu_lnk lnk1 = { &app,1 ,  &drv,246, NULL };
tceu_lnk lnk2 = { &app,2 ,  &drv,245, NULL };
tceu_lnk lnk3 = { &app,3 ,  &drv,244, NULL };
tceu_lnk lnk4 = { &drv,1 ,  &app,243, NULL };

void MAIN (void) {
	APPS = &drv;
	drv.nxt = &app;
    LNKS = &lnk1;
    lnk1.nxt = &lnk2;
    lnk2.nxt = &lnk3;
	lnk3.nxt = &lnk4;
}
