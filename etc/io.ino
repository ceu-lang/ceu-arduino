#include "Arduino.h"

#include <Servo.h>
Servo myservo;

void setup ()
{
}

void loop()
{
    // MOTOR //
    pinMode(9, OUTPUT);
    for (int i=0; i<256; i++) {
        analogWrite(9, i);
        delay(10);
    }
    delay(2000);
    for (int i=255; i>=0; i--) {
        analogWrite(9, i);
        delay(10);
    }
    analogWrite(9, 0);

    // SERVO //
/*
    myservo.attach(10);
    for (int i=0; i<2; i++) {
        myservo.write(0);
        delay(1000);
        myservo.write(45);
        delay(1000);
        myservo.write(90);
        delay(1000);
        myservo.write(135);
        delay(1000);
        myservo.write(180);
        delay(1000);
        myservo.write(135);
        delay(1000);
        myservo.write(90);
        delay(1000);
        myservo.write(45);
        delay(1000);
    }
    myservo.detach();
*/
    pinMode(10,OUTPUT);
    digitalWrite(10, 0);
    delay(2000);
    for (int i=0; i<10; i++) {
        digitalWrite(10, 1);
        delayMicroseconds(500);
        digitalWrite(10, 0);
        delay(20);
    }
    delay(2000);
    for (int i=0; i<10; i++) {
        digitalWrite(10, 1);
        delayMicroseconds(1500);
        digitalWrite(10, 0);
        delay(20);
    }
    delay(2000);
    for (int i=0; i<10; i++) {
        digitalWrite(10, 1);
        delayMicroseconds(3000);
        digitalWrite(10, 0);
        delay(20);
    }
/*
    delay(10000);

    //
    // The pulses are 20ms apart (50Hz).
    // 1.0ms to 1.25ms pulse length produces 0 degrees.
    // 1.5ms pulse length produces 90 degrees (neutral).
    // 1.75ms to 2.0ms pulse length produces 180 degrees.
    // It might need a little calibration to be exact.
    // The servo might not move 180 degrees but only 20 degrees to 160 degrees.
    //
    pinMode(10,OUTPUT);
    for (int i=0; i<3500; i+=50) {
        digitalWrite(10, 1);
        delayMicroseconds(i);
        digitalWrite(10, 0);
        delay(100);
    }
*/

    // PIEZO //
    pinMode(11, OUTPUT);
    long dur = 1000000;
    for (int tone=900; tone<3000; tone+=200) {
        for (long i=0; i<dur; i+=tone*2) {
            digitalWrite(11, HIGH);
            delayMicroseconds(tone);
            digitalWrite(11, LOW);
            delayMicroseconds(tone);
        }
    }

    // TEMPERATURE //
    Serial.begin(9600);
    float tmp;
    for (int i=0; i<5; i++) {
        tmp = (analogRead(0)*0.004882814 - 0.5) * 100;
        Serial.print("TEMP: ");
        Serial.println(tmp);
        delay(1000);
    }

    // RGB LED //
    pinMode(5, OUTPUT);     // R
    pinMode(6, OUTPUT);     // G
    pinMode(7, OUTPUT);     // B
    if (tmp > 28) {
        analogWrite(5, 128);
        analogWrite(6, 0);
        analogWrite(7, 0);
    } else {
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 128);
    }

    // FLEX //
    float flx;
    for (int i=0; i<10; i++) {
        flx = analogRead(1) * 0.004882814 ;
        Serial.print("FLEX: ");
        Serial.println(flx);
        delay(500);
    }

    // PRESSURE //
    float prs;
    for (int i=0; i<10; i++) {
        prs = analogRead(2) * 0.004882814 ;
        Serial.print("PRESSURE: ");
        Serial.println(prs);
        delay(500);
    }
}
