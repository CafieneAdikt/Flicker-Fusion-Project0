#include <Arduino.h>

// declare variables

 byte ADpin = 14;   // pin assigned to variable
 int AD0 = 0;       // raw A/D converter value
 unsigned long interval = 0;  // mapped analog input
 long intervalInseconds = 0; 
 int LED = 6;       // assign pin 6 to led
 const int INTBUTTON = 16; // interupt button
 bool Buttonpressed = false; // flag for button
 const unsigned long DEBOUNCE_TIME_MS = 100;  
 unsigned long previousdebounce = 0;
 unsigned long previousmillis = 0; // will store last time led was updated
 long frequency = 0; // frequency of the led

  void Buttonpressed_ISR(){
      // send flag high
      Buttonpressed = true;
  
}
 


void setup() {

    Serial.begin(115200); // set baud rate
    pinMode(ADpin,INPUT);
    pinMode(LED,OUTPUT);
    pinMode(INTBUTTON,INPUT_PULLUP); // interupt button
    attachInterrupt(digitalPinToInterrupt(INTBUTTON),Buttonpressed_ISR,FALLING);

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

    intervalInseconds = interval/1000;

    frequency = 1/(2*intervalInseconds);

    if(Buttonpressed && ((currentmillis-previousdebounce) >= DEBOUNCE_TIME_MS)){
        previousdebounce = currentmillis; // set new debounce time
        Serial.println(String(frequency) + "Hz");
        // reset flag
        Buttonpressed = false; 
    }

}

