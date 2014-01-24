#include "ceu_os.h"

extern void MAIN (void);
extern tceu_app* APPS;
extern tceu_lnk* LNKS;

u32 old;
int dt () {
    u32 now = micros();
    int dt = now - old;     // no problems with overflow
    old = now;
    return dt;
}

void setup ()
{
	MAIN();
    old = micros();
	ceu_scheduler_static(APPS, LNKS, dt);
	delay(10);
}

void loop()
{
}

