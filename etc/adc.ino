#include "Arduino.h"

void setup ()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    int i;

#if 0
    int light = analogRead(0);
#else
    int pin = 0;
    ADMUX  = (DEFAULT<<6) | (pin & 0x7);   // channel pin
    ADCSRA = ADCSRA | (1 << ADSC);         // start conversion
    while (ADCSRA & (1 << ADSC));          // wait for conversion
    uint8_t low  = ADCL;
    uint8_t high = ADCH;
    int light = (high<<8) | low;           // read value
#endif

    int dt = map(light, 0,1024, 100,1000);
    for (i=0; i<5; i++) {
        digitalWrite(13, 1);
        delay(dt);
        digitalWrite(13, 0);
        delay(dt);
    }
}
