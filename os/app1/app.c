#include "ceu_os.h"

extern tceu_app serial_drv;
extern tceu_app serial_app;
extern tceu_app gpio_drv;
extern tceu_app gpio_app;

tceu_app* APPS = NULL;
tceu_lnk* LNKS = NULL;

tceu_lnk lnk1 = { &serial_app,1  ,  &serial_drv,246, NULL };
tceu_lnk lnk2 = { &serial_app,2  ,  &serial_drv,245, NULL };
tceu_lnk lnk3 = { &serial_app,3  ,  &serial_drv,244, NULL };
tceu_lnk lnk4 = { &serial_drv,1  ,  &serial_app,243, NULL };

tceu_lnk lnk5 = { &gpio_app,1    ,  &gpio_drv,246, NULL };
tceu_lnk lnk6 = { &gpio_app,2    ,  &gpio_drv,245, NULL };
tceu_lnk lnk7 = { &gpio_drv,1    ,  &gpio_app,244, NULL };

void MAIN (void) {
	APPS           = &serial_drv;
	serial_drv.nxt = &serial_app;
	serial_app.nxt = &gpio_drv;
	gpio_drv.nxt   = &gpio_app;

	LNKS = &lnk1;
	lnk1.nxt = &lnk2;
	lnk2.nxt = &lnk3;
	lnk3.nxt = &lnk4;
	lnk4.nxt = &lnk5;
	lnk5.nxt = &lnk6;
	lnk6.nxt = &lnk7;
}
