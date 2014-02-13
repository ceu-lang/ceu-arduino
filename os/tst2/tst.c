#include "ceu_os.h"

extern int GPIO_SIZE;
extern void gpio_init (tceu_app* app);
extern int APP1_SIZE;
extern void app1_init (tceu_app* app);
extern int APP2_SIZE;
extern void app2_init (tceu_app* app);
extern int SHELL_SIZE;
extern void shell_init (tceu_app* app);

char gpio_data[100];
char app1_data[100];
char app2_data[100];
char shell_data[100];

tceu_app gpio;
tceu_app app1;
tceu_app app2;
tceu_app shell;

tceu_lnk lnk1 = { &app1,1   ,  &gpio,245, NULL };
tceu_lnk lnk2 = { &app1,2   ,  &gpio,244, NULL };
tceu_lnk lnk3 = { &app2,1   ,  &gpio,245, NULL };
tceu_lnk lnk4 = { &app2,2   ,  &gpio,244, NULL };

void MAIN (void) {
    gpio.data = (tceu_org*) gpio_data;
    gpio.init = gpio_init;
    gpio.sys_vec = CEU_SYS_VEC;

    app1.data = (tceu_org*) app1_data;
    app1.init = app1_init;
    app1.sys_vec = CEU_SYS_VEC;

    app2.data = (tceu_org*) app2_data;
    app2.init = app2_init;
    app2.sys_vec = CEU_SYS_VEC;

    shell.data = (tceu_org*) shell_data;
    shell.init = shell_init;
    shell.sys_vec = CEU_SYS_VEC;

	ceu_sys_link(&lnk1);
	ceu_sys_link(&lnk2);
	ceu_sys_link(&lnk3);
	ceu_sys_link(&lnk4);
	ceu_sys_start(&gpio);
	ceu_sys_start(&shell);
}
