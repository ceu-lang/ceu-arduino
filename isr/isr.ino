void __ceu_dummy_to_arduino_include_headers (void);
    /* HACK: any function prototype suffices for the Arduino build system to
     *       include appropriate headers. */

#include "common.h"

#include "wiring_private.h"
#ifdef __AVR
#include <avr/interrupt.h>
#else
#error "Unsupported Platform!"
#endif

#include "_ceu_app.h"

static volatile voidFuncPtr isrs[_VECTORS_SIZE];

#define ceu_out_isr_attach(f,num,mode) ceu_sys_isr_attach(f,num,mode)
#define ceu_out_isr_detach(f,num,mode) ceu_sys_isr_detach(f,num,mode)

void ceu_sys_isr_attach (voidFuncPtr f, int num, int mode) {
    if (num < EXTERNAL_NUM_INTERRUPTS) {
        attachInterrupt(num, f, mode);
    } else {
        isrs[num] = f;
    }
}

void ceu_sys_isr_detach (voidFuncPtr f, int num, int mode) {
    if (num < EXTERNAL_NUM_INTERRUPTS) {
        detachInterrupt(num);
    } else {
        isrs[num] = NULL;
    }
}

#ifdef CEU_ISR__TIMER1_COMPA_vect_num
ISR(TIMER1_COMPA_vect)
{
    //static int v = 0;
    //digitalWrite(12, v=!v);
    if (isrs[TIMER1_COMPA_vect_num] != NULL) {
        isrs[TIMER1_COMPA_vect_num]();
    }
}
#endif

#ifdef CEU_ISR__TIMER1_OVF_vect_num
ISR(TIMER1_OVF_vect)
{
    //static int v = 0;
    //digitalWrite(12, v=!v);
    if (isrs[TIMER1_OVF_vect_num] != NULL) {
        isrs[TIMER1_OVF_vect_num]();
    }
}
#endif

byte CEU_DATA[sizeof(CEU_Main)];
tceu_app CEU_APP;

#include "_ceu_app.c.h"

void setup ()
{
    //pinMode(12, OUTPUT);
    //Serial.begin(9600);

    int i;
    for (i=0; i<_VECTORS_SIZE; i++) {
        isrs[i] = NULL;
    }

    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    ceu_go_all(&CEU_APP);
}

void loop()
{
}
