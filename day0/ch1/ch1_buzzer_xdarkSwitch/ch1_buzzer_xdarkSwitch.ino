/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 *Side project based off the solar simulation and buzzer lessons
 * the project generally turns the led light and triggers the buzzer on when it gets dark or its room level
 * if its bright turn off and hear a different buzzer tone
 */

#include "Arduino.h"

const uint8_t LIGHT = 22;          // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;   // Button (light switch) on pin 23
const uint8_t PHOTO_SENSOR = A8;  // Photoresistor input simulating battery charge rate
const uint8_t ALARM_PIN = 26;      // Active buzzer simulating our alarm speakers

const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed
const uint8_t ON = HIGH;           // Lights are ON when pin is HIGH
const uint8_t OFF = LOW;           // Lights are OFF when pin is LOW
const float HIGH_INTENSITY_LIMIT = 300;  //Average room photo intensity, adjust depending on the brightness you want the light to turn off (0-1023)


void setup() {
  // Intialize Serial class, used to communicate with the Arduino IDE Serial Monitor
  Serial.begin(9600);  // Initialize Serial, set speed to 9600 bits/second (baud)
  while (!Serial) {
    ;  // wait for serial port to connect.
  }
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
  pinMode(PHOTO_SENSOR, INPUT);        // Photoresistor analog input
  pinMode(ALARM_PIN, OUTPUT);           // Set Alarm pin to OUTPUT
}


bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

void loop() {
  int current_intensity = analogRead(PHOTO_SENSOR);  // Read from our photoresistor (0-1023)

  // If out light on and its bright, turn light off, if its dark turn it on
  if (light_on && current_intensity > HIGH_INTENSITY_LIMIT) {
    digitalWrite(LIGHT, OFF);  // Light is on, turn it off
    light_on = false;          // ... and save it's new state
    Serial.print("Turning off");
    tone(ALARM_PIN, 587);
    delay(1000);
    noTone(ALARM_PIN);

  }  else if (!light_on && current_intensity < HIGH_INTENSITY_LIMIT) {
    digitalWrite(LIGHT, ON);  // Light is off, turn it on
    light_on = true;          // ... and save it's new state
    Serial.print("Turning on");
    tone(ALARM_PIN, 800);
    delay(1000);
    noTone(ALARM_PIN);
  }

  // =========== Second part of loop is our prior button / LED control

  // Since we only use the button state *inside* loop() we declare it here as a local variable.
  uint8_t button_state = digitalRead(LIGHT_BUTTON);  // read current button state and save it

  // first check to see if the button state has changed since last loop()
  if (button_state != previous_button_state) {
    if (button_state == PRESSED) {  // if our NEW state is PRESSED this is a new button press
      // then toggle our light, turning it of if it's on, and on if it's off.
      if (light_on) {
        digitalWrite(LIGHT, LOW);   // Light is on, turn it off
        light_on = false;           // ... and save it's new state
      } else {                      // Light must be off
        digitalWrite(LIGHT, HIGH);  // turn on light
        light_on = true;            // ... and save it's new state
      }
    }
    // Since button state changed, let's save its current state for next time through loop()
    previous_button_state = button_state;
  }
}
