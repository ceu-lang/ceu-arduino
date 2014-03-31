#include "Arduino.h"

extern "C" {
    #include "math.hh"
}

long math_map (long x, long in_min, long in_max, long out_min, long out_max)
{
    return map(x,in_min,in_max,out_min,out_max);
}

void math_randomSeed (int seed) {
    randomSeed(seed);
}

int math_random (int min, int max) {
    return random(min, max);
}
