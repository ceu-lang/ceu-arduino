//#define POLLING_INTERVAL 100000    // in microseconds

#define ceu_out_emit_PIN00(v) digitalWrite( 0, v)
#define ceu_out_emit_PIN01(v) digitalWrite( 1, v)
#define ceu_out_emit_PIN02(v) digitalWrite( 2, v)
#define ceu_out_emit_PIN03(v) digitalWrite( 3, v)
#define ceu_out_emit_PIN04(v) digitalWrite( 4, v)
#define ceu_out_emit_PIN05(v) digitalWrite( 5, v)
#define ceu_out_emit_PIN06(v) digitalWrite( 6, v)
#define ceu_out_emit_PIN07(v) digitalWrite( 7, v)
#define ceu_out_emit_PIN08(v) digitalWrite( 8, v)
#define ceu_out_emit_PIN09(v) digitalWrite( 9, v)
#define ceu_out_emit_PIN10(v) digitalWrite(10, v)
#define ceu_out_emit_PIN11(v) digitalWrite(11, v)
#define ceu_out_emit_PIN12(v) digitalWrite(12, v)
#define ceu_out_emit_PIN13(v) digitalWrite(13, v)

#include "_ceu_app.src"

u32 old;

int _ceu_arduino_V;

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

    old = micros();

    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    CEU_APP.init(&CEU_APP);
#ifdef CEU_IN_START
    ceu_go_event(&CEU_APP, CEU_IN_START, NULL);
#endif
}

void loop()
{
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
        ceu_go_event(&CEU_APP, CEU_IN_PIN00, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN01
    tmp = digitalRead(1);
    if (bitRead(_ceu_arduino_V,1) != tmp) {
        bitWrite(_ceu_arduino_V,1,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN01, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN02
    tmp = digitalRead(2);
    if (bitRead(_ceu_arduino_V,2) != tmp) {
        bitWrite(_ceu_arduino_V,2,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN02, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN03
    tmp = digitalRead(3);
    if (bitRead(_ceu_arduino_V,3) != tmp) {
        bitWrite(_ceu_arduino_V,3,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN03, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN04
    tmp = digitalRead(4);
    if (bitRead(_ceu_arduino_V,4) != tmp) {
        bitWrite(_ceu_arduino_V,4,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN04, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN05
    tmp = digitalRead(5);
    if (bitRead(_ceu_arduino_V,5) != tmp) {
        bitWrite(_ceu_arduino_V,5,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN05, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN06
    tmp = digitalRead(6);
    if (bitRead(_ceu_arduino_V,6) != tmp) {
        bitWrite(_ceu_arduino_V,6,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN06, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN07
    tmp = digitalRead(7);
    if (bitRead(_ceu_arduino_V,7) != tmp) {
        bitWrite(_ceu_arduino_V,7,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN07, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN08
    tmp = digitalRead(8);
    if (bitRead(_ceu_arduino_V,8) != tmp) {
        bitWrite(_ceu_arduino_V,8,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN08, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN09
    tmp = digitalRead(9);
    if (bitRead(_ceu_arduino_V,9) != tmp) {
        bitWrite(_ceu_arduino_V,9,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN09, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN10
    tmp = digitalRead(10);
    if (bitRead(_ceu_arduino_V,10) != tmp) {
        bitWrite(_ceu_arduino_V,10,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN10, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN11
    tmp = digitalRead(11);
    if (bitRead(_ceu_arduino_V,11) != tmp) {
        bitWrite(_ceu_arduino_V,11,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN11, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN12
    tmp = digitalRead(12);
    if (bitRead(_ceu_arduino_V,12) != tmp) {
        bitWrite(_ceu_arduino_V,12,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN12, (void*)tmp);
    }
#endif

#ifdef CEU_IN_PIN13
    tmp = digitalRead(13);
    if (bitRead(_ceu_arduino_V,13) != tmp) {
        bitWrite(_ceu_arduino_V,13,tmp);
        ceu_go_event(&CEU_APP, CEU_IN_PIN13, (void*)tmp);
    }
#endif

#ifdef CEU_IN_SERIAL
    if (Serial.available() > 0) {
        char c = Serial.read();
        ceu_go_event(&CEU_APP, CEU_IN_SERIAL, c);
    }
#endif

    u32 now = micros();
    s32 dt = now - old;     // no problems with overflow

    old = now;
    ceu_sys_go(&CEU_APP, CEU_IN__WCLOCK, (tceu_evtp)dt);


#ifdef POLLING_INTERVAL
    delay(POLLING_INTERVAL / 1000);
    delayMicroseconds(POLLING_INTERVAL % 1000);
#endif

#ifdef CEU_ASYNCS
    ceu_sys_go(&CEU_APP, CEU_IN__ASYNC, (tceu_evtp)NULL);
#endif
}
