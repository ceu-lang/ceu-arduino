#include "ceu_os.h"

extern int GPIO_SIZE;
extern void gpio_init (tceu_app* app);
extern int GPIO_TST_SIZE;
extern void gpio_tst_init (tceu_app* app);

extern int SERIAL_SIZE;
extern void serial_init (tceu_app* app);
extern int SERIAL_TST_SIZE;
extern void serial_tst_init (tceu_app* app);

char gpio_data[100];   // TODO: = malloc(GPIO_SIZE);
char gpio_tst_data[100];   // TODO: = malloc(GPIO_SIZE);
char serial_data[100]; // TODO: = malloc(GPIO_SIZE);
char serial_tst_data[100]; // TODO: = malloc(GPIO_SIZE);

tceu_app gpio;
tceu_app gpio_tst;
tceu_app serial;
tceu_app serial_tst;

tceu_lnk lnk1 = { &serial_tst,1  ,  &serial,245, NULL };
tceu_lnk lnk2 = { &serial_tst,2  ,  &serial,244, NULL };
tceu_lnk lnk3 = { &serial_tst,3  ,  &serial,243, NULL };
tceu_lnk lnk4 = { &serial,1      ,  &serial_tst,242, NULL };

tceu_lnk lnk5 = { &gpio_tst,1    ,  &gpio,245, NULL };
tceu_lnk lnk6 = { &gpio_tst,2    ,  &gpio,244, NULL };
tceu_lnk lnk7 = { &gpio,1        ,  &gpio_tst,243, NULL };

void MAIN (void) {
    gpio.data = (tceu_org*) gpio_data;
    gpio.init = gpio_init;
    gpio.sys_vec = CEU_SYS_VEC;

    gpio_tst.data = (tceu_org*) gpio_tst_data;
    gpio_tst.init = gpio_tst_init;
    gpio_tst.sys_vec = CEU_SYS_VEC;

    serial.data = (tceu_org*) serial_data;
    serial.init = serial_init;
    serial.sys_vec = CEU_SYS_VEC;

    serial_tst.data = (tceu_org*) serial_tst_data;
    serial_tst.init = serial_tst_init;
    serial_tst.sys_vec = CEU_SYS_VEC;

	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);
	ceu_sys_link(&lnk4);
    ceu_sys_start(&serial);
	ceu_sys_start(&serial_tst);

	ceu_sys_link(&lnk5);
	ceu_sys_link(&lnk6);
	ceu_sys_link(&lnk7);
    ceu_sys_start(&gpio);
	ceu_sys_start(&gpio_tst);
}
