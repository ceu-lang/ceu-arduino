#include "Arduino.h"

void boot_program_page (uint32_t page, uint8_t* buf);

void setup (void)
{
    uint8_t c[256] = "0123456789";
    int i;
    for(i=10; i<256; i++)
        c[i] = 0xDD;

    typeof(boot_program_page)* PROG = (typeof(PROG)) 0x7ED5;
    PROG(0x6000 + i*256, c);

    pinMode(13, 1);
    digitalWrite(13, 1);
}

void loop (void) {}
