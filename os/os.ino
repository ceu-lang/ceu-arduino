extern "C" {
    #include "ceu_os.h"
    extern void MAIN (void);
}

u32 old;
int dt () {
    u32 now = micros();
    int dt = now - old;     // no problems with overflow
    old = now;
    return dt;
}

#include "Arduino.h"

void setup ()
{
	MAIN();
    old = micros();
    ceu_scheduler(dt);
	delay(10);
}

void loop()
{
}
