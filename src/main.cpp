#include <Arduino.h>

// declare variables

 byte ADpin = 14;   // pin assigned to variable
 int AD0 = 0;       // raw A/D converter value
 int mapDelay = 0;  // mapped analog input
 int LED = 6;       // assign pin 6 to led

void setup() {

    Serial.begin(115200); // set baud rate
    pinMode(ADpin,INPUT);
    pinMode(LED,OUTPUT);

}

void loop() {

    AD0 = analogRead(ADpin);    // read input from potentiometer

    mapDelay = map(AD0, 0, 1023, 50, 1); // map 10bit number to a interval to cause flicker fusion

 // Same time on/off for 50% dutycycle
    digitalWrite(LED,HIGH);
    delay(mapDelay);

    digitalWrite(LED,LOW);
    delay(mapDelay);

// serial interface
   Serial.println(mapDelay);


}