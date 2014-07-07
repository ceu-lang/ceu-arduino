#include "EEPROM.h"
#include "SPI.h"
#include "GD2.h"

#include "_ceu_app.src"

u32 old;
byte CEU_DATA[sizeof(CEU_Main)];
tceu_app CEU_APP;

#define CEU_IN_SERIAL 100

void setup ()
{
#ifdef CEU_IN_SERIAL
    Serial.begin(9600);
#endif
    GD.begin();
    //GD.finish();

    old = micros();

    CEU_APP.data = (tceu_org*) &CEU_DATA;
    CEU_APP.init = &ceu_app_init;
    CEU_APP.init(&CEU_APP);
#ifdef CEU_IN_START
    ceu_sys_go(&CEU_APP, CEU_IN_START, CEU_EVTP((void*)NULL));
#endif
}

void loop()
{
#ifdef CEU_IN_SERIAL
    if (Serial.available() > 0) {
        char c = Serial.read();
        ceu_sys_go(&CEU_APP, CEU_IN_SERIAL, CEU_EVTP(c));
    }
#endif

    u32 now = micros();
    s32 dt = now - old;     // no problems with overflow
    old = now;
    ceu_sys_go(&CEU_APP, CEU_IN__WCLOCK, CEU_EVTP(dt));

#ifdef CEU_ASYNCS
    ceu_sys_go(&CEU_APP, CEU_IN__ASYNC, CEU_EVTP((void*)NULL));
#endif

#ifdef CEU_IN_GD_TOUCH
    GD.get_inputs();
    if (GD.inputs.x != -32768) {
        // only generate touch events if the user clicked on screen
        tceu__int__int__int v = { GD.inputs.x<<4, GD.inputs.y<<4, GD.inputs.tag };
        ceu_sys_go(&CEU_APP, CEU_IN_GD_TOUCH, CEU_EVTP((void*)&v));
    }
#endif

#ifdef CEU_IN_GD_REDRAW
    //GD.ClearColorRGB(0xe0e0e0);
    GD.Clear();
    //GD.cmd_gradient(0, 0, 0xa0a4f7, 0, 272, 0xd0f4f7);
    ceu_sys_go(&CEU_APP, CEU_IN_GD_REDRAW, CEU_EVTP((void*)NULL));
    GD.swap();
#endif
}
