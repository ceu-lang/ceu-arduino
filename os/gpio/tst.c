#include "ceu_os.h"

extern int GPIO_SIZE;
extern void gpio_init (tceu_app* app);

extern int TST_SIZE;
extern void tst_init (tceu_app* app);

char gpio_data[300]; // TODO: = malloc(GPIO_SIZE);
char tst_data[300];  // TODO: = malloc(TST_SIZE);

tceu_app gpio;
tceu_app tst;

tceu_lnk lnk1 = { &tst,1   ,  &gpio,245, NULL };
tceu_lnk lnk2 = { &tst,2   ,  &gpio,244, NULL };
tceu_lnk lnk3 = { &gpio,1  ,  &tst,243,  NULL };

void MAIN (void) {
    gpio.data = (tceu_org*) gpio_data;
    gpio.init = gpio_init;
    gpio.sys_vec = CEU_SYS_VEC;

    tst.data = (tceu_org*) tst_data;
    tst.init = tst_init;
    tst.sys_vec = CEU_SYS_VEC;

    ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);

    ceu_sys_start(&gpio);
	ceu_sys_start(&tst);
}
