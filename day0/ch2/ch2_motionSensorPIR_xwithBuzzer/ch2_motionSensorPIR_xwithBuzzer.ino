/*
 * Day 0 - AI Apocalypse by inventr.io
 * - Potentiometer
 * - Pulse Width Modulation (PWM)
 * Adding a buzzer to the PIR lesson to go off for 2 seconds when motion is detected
 */
#include "Arduino.h"

const int FLOOD_LIGHTS = 22;   // Flood lights attached to pin 22
const int MOTION_SENSOR = 23;  // PIR motion sensor pin
const uint8_t ALARM_PIN = 24;      // Active buzzer simulating our alarm speakers

const uint8_t ON = HIGH;
const uint8_t OFF = LOW;

bool previous_motion = false;  // previous state of motion sensor's pin

void setup() {
  Serial.begin(9600);             // initialize serial
  pinMode(MOTION_SENSOR, INPUT);  // set arduino pin to input mode
  pinMode(FLOOD_LIGHTS, OUTPUT);  // set arduino pin to output mode
  pinMode(ALARM_PIN, OUTPUT);
}

unsigned long start_time;
unsigned long delay_start = 0;
const uint8_t DELAY_SECONDS = 5;

void loop() {
  bool motion_detected = digitalRead(MOTION_SENSOR);  // read new state

  if (motion_detected && !previous_motion) {  // New motion detected
    Serial.println("Motion detected!");
    digitalWrite(FLOOD_LIGHTS, ON);  // turn on flood lights!
    tone(ALARM_PIN, 800);
    delay_start = 0;                 // stop delay timer when motion detected
    start_time = millis();
  } else if (!motion_detected && previous_motion) {  // motion delay expired
    noTone(ALARM_PIN);
    float seconds = (millis() - start_time) / 1000.0;
    Serial.print("Motion stopped after ");
    Serial.print(seconds);
    Serial.println(" seconds.");
    delay_start = millis();  // Start delay timer
  }

  // If flood lights are on and our timer expires then turn off the lights
  if (delay_start && (millis() - delay_start) / 1000 >= DELAY_SECONDS) {
    float seconds = (millis() - start_time) / 1000.0;
    Serial.print("Lights out after ");
    Serial.print(seconds);
    Serial.println(" seconds.");
    digitalWrite(FLOOD_LIGHTS, OFF);  // turn off the flood lights
    delay_start = 0;
  }

  previous_motion = motion_detected;
  delay(10);
}