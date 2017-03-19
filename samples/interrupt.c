
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
const byte inputPin = 7 // the datapin of humidity dht11 sensor connected to pin 7


void setup(){
 Serial.begin(9600);
  pinMode(inputPin,INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);// here I have used the digital pin 2 as interrupt 
/*
 SREG = B00000001; // setting the SREG enabled for the pin INT0 thus pin 2
 EIMSK = B00000001; // setting the EIMSK enabled for the pin INT0 thus pin 2
*/

}

void loop() {
    if (state == HIGH){
      int humVal = analogRead(7);
      if( humVal > 300){
        Serial.println("Environment is Okay");
      }else{
        Serial.println("Environment is not Okay");
      }
    }
/*
Instead of the attachInterrupt you can also try by setting value B0000001, thus INT0 equals to 1;
// this will function as same as above loop...
if ( EIFR == B00000001){
      int humVal = analogRead(7);
      if( humVal > 300){
        Serial.println("Environment is Okay");
      }else{
        Serial.println("Environment is not Okay");
      }
}
*/
}

void blink(){
  state = !state;
}

 
/*
 * 
 *  THIS IS CASE USING dht.h library...
 *  
 *  
#include <dht.h>

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
const byte inputPin = 7 // the datapin of humidity dht11 sensor connected to pin 7
#define DHT_11PIN 7;
dht DHT;

void setup(){
 Serial.begin(9600);
  pinMode(inputPin,INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);// here I have used the digital pin 2 as interrupt 
}

void loop() {
    if (state == HIGH){
      int humCheck = DHT.read11(7);
      if(humCheck >= 0){
          int humVal = DHT.humidity;
          // like this we can obtain temperature value DHT.temperature;
          if( humVal > 30){
            Serial.println("Environment is Okay");
          }else{
            Serial.println("Environment is not Okay");
          }
      }
   
    }
}

void blink(){
  state = !state;
}
 
*/
