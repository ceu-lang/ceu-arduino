void __ceu_dummy_to_arduino_include_headers (void);
    /* HACK: any function prototype suffices for the Arduino build system to
     *       include appropriate headers. */

#include "common.h"

#include "_ceu_app.h"
void _attachInterrupt(u8 interruptNum, void (*userFunc)(tceu_app*,CEU_Main*), int mode);
void _detachInterrupt(uint8_t interruptNum);
#define ceu_out_isr_on(f,num,mode)  _attachInterrupt(num, f, mode);
#define ceu_out_isr_off(f,num,mode) _detachInterrupt(num);

#include "_ceu_app.c.h"

void setup ()
{
    ceu_go_all(NULL);
}

void loop()
{
}
