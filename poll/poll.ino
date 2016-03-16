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
#ifdef CEU_OUT_PIN00
    pinMode( 0, OUTPUT);
#endif
#ifdef CEU_IN_PIN01
    pinMode( 1, INPUT);
#endif
#ifdef CEU_OUT_PIN01
    pinMode( 1, OUTPUT);
#endif
#ifdef CEU_IN_PIN02
    pinMode( 2, INPUT);
#endif
#ifdef CEU_OUT_PIN02
    pinMode( 2, OUTPUT);
#endif
#ifdef CEU_IN_PIN03
    pinMode( 3, INPUT);
#endif
#ifdef CEU_OUT_PIN03
    pinMode( 3, OUTPUT);
#endif
#ifdef CEU_IN_PIN04
    pinMode( 4, INPUT);
#endif
#ifdef CEU_OUT_PIN04
    pinMode( 4, OUTPUT);
#endif
#ifdef CEU_IN_PIN05
    pinMode( 5, INPUT);
#endif
#ifdef CEU_OUT_PIN05
    pinMode( 5, OUTPUT);
#endif
#ifdef CEU_IN_PIN06
    pinMode( 6, INPUT);
#endif
#ifdef CEU_OUT_PIN06
    pinMode( 6, OUTPUT);
#endif
#ifdef CEU_IN_PIN07
    pinMode( 7, INPUT);
#endif
#ifdef CEU_OUT_PIN07
    pinMode( 7, OUTPUT);
#endif
#ifdef CEU_IN_PIN08
    pinMode( 8, INPUT);
#endif
#ifdef CEU_OUT_PIN08
    pinMode( 8, OUTPUT);
#endif
#ifdef CEU_IN_PIN09
    pinMode( 9, INPUT);
#endif
#ifdef CEU_OUT_PIN09
    pinMode( 9, OUTPUT);
#endif
#ifdef CEU_IN_PIN10
    pinMode(10, INPUT);
#endif
#ifdef CEU_OUT_PIN10
    pinMode(10, OUTPUT);
#endif
#ifdef CEU_IN_PIN11
    pinMode(11, INPUT);
#endif
#ifdef CEU_OUT_PIN11
    pinMode(11, OUTPUT);
#endif
#ifdef CEU_IN_PIN12
    pinMode(12, INPUT);
#endif
#ifdef CEU_OUT_PIN12
    pinMode(12, OUTPUT);
#endif
#ifdef CEU_IN_PIN13
    pinMode(13, INPUT);
#endif
#ifdef CEU_OUT_PIN13
    pinMode(13, OUTPUT);
#endif

#if defined(CEU_IN__WCLOCK) || defined(CEU_IN_DT)
    old = millis();
#endif

    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    CEU_APP.init(&CEU_APP);
#ifdef CEU_IN_START
    ceu_sys_go(&CEU_APP, CEU_IN_START, NULL);
#endif
}

void loop()
{
#if defined(CEU_TIMEMACHINE) || POLLING_INTERVAL
#ifndef POLLING_INTERVAL
#error TM must define POLLING_INTERVAL
#endif
    int tm = (CEU_TIMEMACHINE_ON ? 0 : POLLING_INTERVAL);
#ifdef CEU_ASYNCS
    if (CEU_APP.pendingAsyncs) {
        //tm = 0;
    }
#endif
#endif

#if defined(CEU_IN__WCLOCK) || defined(CEU_IN_DT)

    u32 now = millis();
    s32 dt = now - old;     // no problems with overflow

#ifdef POLLING_INTERVAL
    if (tm > 0) {
        if (dt < tm) {
            delay(tm-dt);
            now = millis();
            dt = now - old;
        }
    }
#endif
    s32 dt_us = dt*1000;
    old = now;

#ifdef CEU_TIMEMACHINE
    ceu_sys_go(&CEU_APP, CEU_IN__WCLOCK_, &dt_us);
#endif
if (!CEU_TIMEMACHINE_ON) {
    ceu_sys_go(&CEU_APP, CEU_IN__WCLOCK, &dt_us);
}

#ifdef CEU_IN_DT_
    ceu_sys_go(&CEU_APP, CEU_IN_DT_, &dt);
#endif
#ifdef CEU_IN_DT
if (!CEU_TIMEMACHINE_ON) {
    ceu_sys_go(&CEU_APP, CEU_IN_DT, &dt);
}
#endif

#endif  /* CEU_IN__WCLOCK || CEU_IN_DT */

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
    defined(CEU_IN_PIN10) || \
    defined(CEU_IN_PIN11) || \
    defined(CEU_IN_PIN12) || \
    defined(CEU_IN_PIN13)
    int tmp;
#endif

#ifdef CEU_IN_PIN00
    tmp = digitalRead(0);
    if (bitRead(_ceu_arduino_V,0) != tmp) {
        bitWrite(_ceu_arduino_V,0,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN00, &tmp);
    }
#endif

#ifdef CEU_IN_PIN01
    tmp = digitalRead(1);
    if (bitRead(_ceu_arduino_V,1) != tmp) {
        bitWrite(_ceu_arduino_V,1,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN01, &tmp);
    }
#endif

#ifdef CEU_IN_PIN02
    tmp = digitalRead(2);
    if (bitRead(_ceu_arduino_V,2) != tmp) {
        bitWrite(_ceu_arduino_V,2,tmp);
#ifdef CEU_TIMEMACHINE
#ifdef CEU_IN_PIN02_
        ceu_sys_go(&CEU_APP, CEU_IN_PIN02_, &tmp);
#endif
#endif
if (!CEU_TIMEMACHINE_ON) {
        ceu_sys_go(&CEU_APP, CEU_IN_PIN02, &tmp);
}
    }
#endif

#ifdef CEU_IN_PIN03
    tmp = digitalRead(3);
    if (bitRead(_ceu_arduino_V,3) != tmp) {
        bitWrite(_ceu_arduino_V,3,tmp);
#ifdef CEU_TIMEMACHINE
#ifdef CEU_IN_PIN03_
        ceu_sys_go(&CEU_APP, CEU_IN_PIN03_, &tmp);
#endif
#endif
if (!CEU_TIMEMACHINE_ON) {
        ceu_sys_go(&CEU_APP, CEU_IN_PIN03, &tmp);
}
    }
#endif

#ifdef CEU_IN_PIN04
    tmp = digitalRead(4);
    if (bitRead(_ceu_arduino_V,4) != tmp) {
        bitWrite(_ceu_arduino_V,4,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN04, &tmp);
    }
#endif

#ifdef CEU_IN_PIN05
    tmp = digitalRead(5);
    if (bitRead(_ceu_arduino_V,5) != tmp) {
        bitWrite(_ceu_arduino_V,5,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN05, &tmp);
    }
#endif

#ifdef CEU_IN_PIN06
    tmp = digitalRead(6);
    if (bitRead(_ceu_arduino_V,6) != tmp) {
        bitWrite(_ceu_arduino_V,6,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN06, &tmp);
    }
#endif

#ifdef CEU_IN_PIN07
    tmp = digitalRead(7);
    if (bitRead(_ceu_arduino_V,7) != tmp) {
        bitWrite(_ceu_arduino_V,7,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN07, &tmp);
    }
#endif

#ifdef CEU_IN_PIN08
    tmp = digitalRead(8);
    if (bitRead(_ceu_arduino_V,8) != tmp) {
        bitWrite(_ceu_arduino_V,8,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN08, &tmp);
    }
#endif

#ifdef CEU_IN_PIN09
    tmp = digitalRead(9);
    if (bitRead(_ceu_arduino_V,9) != tmp) {
        bitWrite(_ceu_arduino_V,9,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN09, &tmp);
    }
#endif

#ifdef CEU_IN_PIN10
    tmp = digitalRead(10);
    if (bitRead(_ceu_arduino_V,10) != tmp) {
        bitWrite(_ceu_arduino_V,10,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN10, &tmp);
    }
#endif

#ifdef CEU_IN_PIN11
    tmp = digitalRead(11);
    if (bitRead(_ceu_arduino_V,11) != tmp) {
        bitWrite(_ceu_arduino_V,11,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN11, &tmp);
    }
#endif

#ifdef CEU_IN_PIN12
    tmp = digitalRead(12);
    if (bitRead(_ceu_arduino_V,12) != tmp) {
        bitWrite(_ceu_arduino_V,12,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN12, &tmp);
    }
#endif

#ifdef CEU_IN_PIN13
    tmp = digitalRead(13);
    if (bitRead(_ceu_arduino_V,13) != tmp) {
        bitWrite(_ceu_arduino_V,13,tmp);
        ceu_sys_go(&CEU_APP, CEU_IN_PIN13, &tmp);
    }
#endif

#ifdef CEU_IN_SERIAL
    if (Serial.available() > 0) {
        char c = Serial.read();
        ceu_sys_go(&CEU_APP, CEU_IN_SERIAL, &c);
    }
#endif

#ifdef CEU_ASYNCS
    ceu_sys_go(&CEU_APP, CEU_IN__ASYNC, NULL);
#endif
}
