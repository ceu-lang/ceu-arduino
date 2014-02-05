#include "Arduino.h"

extern "C" {
    #include "serial.hh"
}

int serial_if (void) {
    return Serial;
}

int serial_available (void) {
    return Serial.available();
}

void serial_begin (int speed) {
    Serial.begin(speed);
}

void serial_end (void) {
    Serial.end();
}

void serial_write (const uint8_t* buf, size_t len) {
    Serial.write(buf, len);
}

int serial_read (void) {
    return Serial.read();
}
