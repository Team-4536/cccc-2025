#include "slot_machine.h"

// const int M1[4] = {2, 4, 3, 5}; // motor 1 pins
const int M1[4] = {2, 3, 4, 5};     // motor 1 pins   // 2 Blue, 3 Pink, 4 yellow, 5 Orange
const int M2[4] = {6, 7, 8, 9};     // motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // motor 3 pins

const int button_pin = 16; // button input pin
const int led_pin = 15;    // button input pin

void setup()
{
  Serial.begin();
  begin_motors(M1, M2, M3);

  pinMode(button_pin, INPUT_PULLDOWN);
  pinMode(led_pin, OUTPUT);
}

void loop()
{

  Serial.println(digitalRead(button_pin));
  if (digitalRead(button_pin))
  {
    step_motorM1(M1);
    step_motorM2(M2);
    step_motorM3(M3);
    delay(4);
  }
  else
  {
    digitalWrite(led_pin, HIGH);
    delay(250);
    digitalWrite(led_pin, LOW);
    delay(250);
    Serial.println("Hello World");
  }
}
