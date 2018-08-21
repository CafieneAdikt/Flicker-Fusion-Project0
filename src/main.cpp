#include <Arduino.h>

// declare variables

 byte ADpin = 14;   // pin assigned to variable
 int AD0 = 0;       // raw A/D converter value
 long interval = 0;  // mapped analog input
 int LED = 6;       // assign pin 6 to led
 unsigned long previousmillis = 0; // will store last time led was updated


void setup() {

    Serial.begin(115200); // set baud rate
    pinMode(ADpin,INPUT);
    pinMode(LED,OUTPUT);

}

void loop() {
    // variable that stores current time
    unsigned long currentmillis = millis();

    AD0 = analogRead(ADpin);    // read input from potentiometer

    interval = map(AD0, 0, 1023, 50, 1); // map 10bit number to a interval to cause flicker fusion

    if(currentmillis - previousmillis >= interval){
        //save last time it blinks
        previousmillis = currentmillis;

        // change the state of the led to opposite of previous state 
    digitalWrite(LED, !digitalRead(LED));
    }

   // serial interface
   Serial.println(interval);

}