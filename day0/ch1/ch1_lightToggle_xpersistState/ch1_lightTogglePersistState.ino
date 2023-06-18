#include "Arduino.h"


const uint8_t LIGHT = 22;         // LED on pin 22
const uint8_t LIGHT_BUTTON = 23;  // Button (light switch) on pin 23

/*
 * NOTE: While HIGH/LOW now make more sense when using a pull-down resistor, it still
 *       makes even MORE clear using PRESSED / NOT_PRESSED.  However, now we set
 *       PRESSED equal to HIGH.
 */
const uint8_t PRESSED = LOW;       // Button input pin reads LOW when pressed
const uint8_t NOT_PRESSED = HIGH;  // Button input pin reads HIGH when NOT pressed

void setup() {
  pinMode(LIGHT, OUTPUT);               // LED representing our light (output)
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  // Button controlling light (input with pull-up resistor)
}

bool light_on = false;                     // we start with the light turned off
bool previous_button_state = NOT_PRESSED;  // start out with button NOT pressed

/*
 * In the loop we'll check to see if the button has *just* been pressed or released and
 * when it's pressed we'll toggle the light on/off.
 */
void loop() {
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

  delay(50);
}
