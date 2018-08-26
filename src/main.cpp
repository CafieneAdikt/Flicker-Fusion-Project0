#include <Arduino.h>

// declare variables

byte ADpin = 14;            // pin assigned to variable
int AD0 = 0;                // raw A/D converter value
unsigned long interval = 0; // mapped analog input
float intervalInSeconds = 0;
int LED = 6;                         // assign pin 6 to led
const int INTBUTTON = 16;            // interupt button
volatile bool buttonPressed = false; // flag for button
const unsigned long DEBOUNCE_TIME_MS = 200;
unsigned long previousDebounce = 0; 
unsigned long frequency = 0; // frequency of the led

void Buttonpressed_ISR(); // define the ISR

void setup() {

  Serial.begin(115200); // set baud rate
  pinMode(ADpin, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(INTBUTTON, INPUT_PULLUP); // interupt button
  attachInterrupt(digitalPinToInterrupt(INTBUTTON), Buttonpressed_ISR, FALLING);
}

void loop() {

  // will store last time led was updated in the loop
  static unsigned long previousmillis = 0;

  // variable that stores current time
  unsigned long currentmillis = millis();

  AD0 = analogRead(ADpin); // read input from potentiometer

  interval = map(AD0, 0, 1023, 50, 1); // map 10bit number to a interval to cause flicker fusion

  if (currentmillis - previousmillis >= interval) {
    // save last time it blinks
    previousmillis = currentmillis;

    // change the state of the led to opposite of previous state
    digitalWrite(LED, !digitalRead(LED));
  }

   // maths to convert the interval to frequency
  intervalInSeconds = interval / 1000.0;

  frequency = 1 / (2 * intervalInSeconds);
}

void Buttonpressed_ISR() {
  // send flag high
  buttonPressed = true;

  unsigned long currentmillis = millis(); //recheck the time

  if (buttonPressed &&
      ((currentmillis - previousDebounce) >= DEBOUNCE_TIME_MS)) {
    previousDebounce = currentmillis; // set new debounce time
    Serial.println("Flicker Fusion Thresthold Frequency :  " + String(frequency) + "Hz"); // serial monitor output
    // reset flag
    buttonPressed = false;
  }
}