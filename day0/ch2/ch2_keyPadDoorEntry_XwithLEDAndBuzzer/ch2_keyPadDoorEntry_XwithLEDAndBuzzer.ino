/*
 * Day 0 - AI Apocalypse by inventr.io
 * Learn more at https://inventr.io/PLACEHOLDER
 *
 * Building on the keypad door lock lesson, I'm adding a green led to go off when the door is unlocked, a consistent red 
 * light when the door is locked and a buzzer when the wrong code is passed. 
 */

/*
 * Arduino language concepts introduced in this lesson.
 *
 */
#include "Arduino.h"

#include <Keypad.h>         // Library for 4x4 membrane keypad
#include <LiquidCrystal.h>  // LCD1602 library



const byte ROWS = 4;
const byte COLS = 4;

const byte ROW_PINS[ROWS] = { 23, 25, 27, 29 };
const byte COL_PINS[COLS] = { 31, 33, 35, 37 };
const int OPEN_PIN = 34;
const int CLOSED_PIN = 36;
const int BUZZER_PIN = 38;

char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

Keypad security_keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

LiquidCrystal lcd(22, 24, 26, 28, 30, 32);

const String SECRET_CODE = "1234";
const int code_indent = (16 - SECRET_CODE.length()) / 2;
String entered_code = "";
String prompt = "Enter Pass Code";

void setup() {
  pinMode(OPEN_PIN, OUTPUT);
  pinMode(CLOSED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);   // Set LCD resolution (16 columns, 2 rows)
  lcd.clear();
  showPrompt(prompt);
}

void loop() {
  char key = security_keypad.getKey();

  if (key) {
    Serial.print("Key entered: ");
    Serial.println(key);

    // Reset key
    if (key == '*') {
      Serial.println("Reset: starting over");
      lcd.clear();
      showPrompt(prompt);
      entered_code = "";   // Reset back to starting point (nothing entered yet)
      return;             // exits loops here
    }

    // Delete key
    if (key == '#') {
      Serial.println("Delete last character entered");
      lcd.setCursor(code_indent + entered_code.length() - 1, 1);
      lcd.print(" ");
      entered_code = entered_code.substring(0, entered_code.length() - 1);
      Serial.print("  Current entered code: ");
      Serial.println(entered_code);
      return;
    }

    entered_code += key;

    if (entered_code.length() == 1) {
      Serial.println("A code has begun to be entered");
      lcd.clear();
      showPrompt("Complete code");
    }
    lcd.setCursor(code_indent + entered_code.length() - 1, 1);
    lcd.print("*");

    Serial.print("  Current entered code: ");
    Serial.println(entered_code);

    if (entered_code.length() == SECRET_CODE.length()) {
      Serial.println("Entry complete - validating combination");
      lcd.clear();

      if (entered_code == SECRET_CODE) {
        Serial.println("Entered code matches - unlock door for 2 seconds");
        lcd.print("Door Unlocked");
        digitalWrite(OPEN_PIN, HIGH);
        digitalWrite(CLOSED_PIN, LOW);
        delay(2000);
        Serial.println("Re-lock door");
      } else {
        lcd.print("No match");
        tone(BUZZER_PIN, 650);
        lcd.setCursor(0, 1);
        lcd.print("Door is locked");
        digitalWrite(OPEN_PIN, LOW);
        digitalWrite(CLOSED_PIN, HIGH);
        Serial.println("Wrong combination entered");
        delay(2000);
        Serial.println("Door locked");
        noTone(BUZZER_PIN);
      }
      lcd.clear();
      digitalWrite(OPEN_PIN, LOW);
      digitalWrite(CLOSED_PIN, HIGH);
      showPrompt(prompt);
      entered_code = "";
    }
  }
}

void showPrompt(String prompt) {
  int prompt_length = prompt.length();
  Serial.println(prompt.c_str());
  if (prompt_length > 16) {
    Serial.println("Prompt is too long and will be truncated");
    prompt.substring(0, 16);
  }
  int centering_offset = (16 - prompt_length) / 2;
  lcd.setCursor(centering_offset, 0);
  lcd.print(prompt.c_str());
}