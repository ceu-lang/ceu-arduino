#include <stdlib.h>
#include "ceu_os.h"

extern int GPIO_SIZE;
extern void gpio_init (tceu_app* app);

extern int TST_SIZE;
extern void tst_init (tceu_app* app);

char drv_data[300]; // = malloc(GPIO_SIZE);
char tst_data[300]; // = malloc(TST_SIZE);

void MAIN (void) {

    tceu_app drv;
        drv.data = (tceu_org*) drv_data;
        drv.init = gpio_init;
        drv.sys_vec = CEU_SYS_VEC;

    tceu_app tst;
        tst.data = (tceu_org*) tst_data;
        tst.init = tst_init;
        tst.sys_vec = CEU_SYS_VEC;

    tceu_lnk lnk1 = { &tst,1  ,  &drv,245, NULL };
    tceu_lnk lnk2 = { &tst,2  ,  &drv,244, NULL };
    tceu_lnk lnk3 = { &drv,1  ,  &tst,243, NULL };

	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);

	ceu_sys_start(&drv);
	ceu_sys_start(&tst);
}
