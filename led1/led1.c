#include "ceu_os.h"

extern tceu_app drv_gpio;
extern tceu_app app_led1;

tceu_app* APPS;
tceu_lnk* LNKS;
tceu_lnk lnk1 = { &app_led1,1 ,  &drv_gpio,246, NULL };
tceu_lnk lnk2 = { &app_led1,1 ,  &drv_gpio,245, NULL };

void MAIN (void) {
    APPS = &drv_gpio;
    drv_gpio.nxt = &app_led1;
    LNKS = &lnk1;
    lnk1.nxt = &lnk2;
}
