void __ceu_dummy_to_arduino_include_headers (void);
    /* HACK: any function prototype suffices for the Arduino build system to
     *       include appropriate headers. */

#include "common.h"

#include "_ceu_app.h"
#define ceu_out_isr_on(f,num,mode)  digitalWrite(12,1);  attachInterrupt(num, f, mode);
#define ceu_out_isr_off(f,num,mode) digitalWrite(12,0);  detachInterrupt(num);

byte CEU_DATA[sizeof(CEU_Main)];
tceu_app CEU_APP;

#include "_ceu_app.c.h"

void setup ()
{
    pinMode(12, OUTPUT);
    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    ceu_go_all(&CEU_APP);
}

void loop()
{
}
