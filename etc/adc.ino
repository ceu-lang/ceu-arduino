#include "Arduino.h"

void setup ()
{
    pinMode(3, OUTPUT);
}

void loop()
{
    int light = analogRead(0);
    int led   = map(light, 0,1024, 0,16);
    analogWrite(3, led);
}
