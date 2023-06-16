/*
 *
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * A light-emitting diode (LED) is a semiconductor device that emits light
 * when an electric current is passed through it. LEDs are small, efficient,
 * and long-lasting, making them ideal for a wide range of applications such
 * as indicator lights, digital displays, and lighting. They are available
 * in a variety of colors and sizes.
 *
 * Alex Eschenauer
 * David Schmidt
 */

#include "Arduino.h"

const int LIGHT = 22;  // Set "LIGHT" to the HERO XL pin connected to the LED cathode (+) lead

void setup() {
  // initialize digital pin defined by "LIGHT" as an output pin.
  pinMode(LIGHT, OUTPUT);
}

void loop() {                 // Blocks of code are contained between open and close braces ("{}")
  digitalWrite(LIGHT, HIGH);  // Set our designated LIGHT pin to HIGH value (5V), or "on"
  delay(2000);                // Wait for 2 second (2000 microseconds)

  digitalWrite(LIGHT, LOW);  // Now set our pin to LOW voltage (0V), or "off".
  delay(1000);               // Wait one second.
} 
