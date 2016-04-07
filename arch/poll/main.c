//#define POLLING_INTERVAL 30    // in milliseconds

void __ceu_dummy_to_arduino_include_headers (void);
    /* HACK: any function prototype suffices for the Arduino build system to
     *       include appropriate headers. */

#include "common.h"
#include "_ceu_app.h"

#ifdef CEU_TIMEMACHINE
int CEU_TIMEMACHINE_ON = 0;
#else
#define CEU_TIMEMACHINE_ON 0
#endif

#include "_ceu_app.c.h"

#if defined(CEU_IN__WCLOCK) || defined(CEU_IN_DT)
u32 old;
#endif

#if defined(CEU_IN_PIN00) || \
    defined(CEU_IN_PIN01) || \
    defined(CEU_IN_PIN02) || \
    defined(CEU_IN_PIN03) || \
    defined(CEU_IN_PIN04) || \
    defined(CEU_IN_PIN05) || \
    defined(CEU_IN_PIN06) || \
    defined(CEU_IN_PIN07) || \
    defined(CEU_IN_PIN08) || \
    defined(CEU_IN_PIN09) || \
    defined(CEU_IN_PIN00) || \
    defined(CEU_IN_PIN01) || \
    defined(CEU_IN_PIN12) || \
    defined(CEU_IN_PIN13)
int _ceu_arduino_V;
#endif

byte CEU_DATA[sizeof(CEU_Main)];
tceu_app CEU_APP;

void setup ()
{
#ifdef CEU_IN_PIN00
    pinMode( 0, INPUT);
#endif

    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    CEU_APP.init(&CEU_APP);
}

void loop()
{
    u32 now = millis();
    s32 dt = now - old;     // no problems with overflow
    s32 dt_us = dt*1000;
    old = now;

    ceu_sys_go(&CEU_APP, CEU_IN__WCLOCK, &dt_us);

#ifdef CEU_IN_PIN00
    tmp = digitalRead(0);
    if (bitRead(_ceu_arduino_V,0) != tmp) {
        bitWrite(_ceu_arduino_V,0,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN00, &tmp);
    }
#endif
#ifdef CEU_IN_SERIAL
    if (Serial.available() > 0) {
        char c = Serial.read();
        ceu_sys_go(&CEU_APP, CEU_IN_SERIAL, &c);
    }
#endif
}
