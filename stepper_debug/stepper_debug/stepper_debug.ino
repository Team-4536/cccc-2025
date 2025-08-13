#include "slot_machine.h"

// const int M1[4] = {2, 4, 3, 5}; // motor 1 pins
const int M1[4] = {2, 3, 4, 5}; // motor 1 pins   // 2 Blue, 3 Pink, 4 yellow, 5 Orange
const int M2[4] = {6, 7, 8, 9}; // motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // motor 3 pins

const int button_pin = 16; // button input pin

int state = 0;

int remaining_1 = 513;
int remaining_2 = 0;
int remaining_3 = 0;

int seg_1 = 1;
int seg_2 = 2;
int seg_3 = 3;

void setup() {
  Serial.begin();
  randomSeed(analogRead(0));

  for (int i = 0; i < 4; i++) {
    pinMode(M1[i], OUTPUT);
    pinMode(M2[i], OUTPUT);
    pinMode(M3[i], OUTPUT);
  }

  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  if(remaining_1 == 0) {  // one-complete turn testing
    stop_motor(M1);
    delay(1000);
    remaining_1 = 513;  // 513 steps per rotation @ 10ms delay
  } else {
    step_motor(M1);
    remaining_1 = remaining_1 - 1;
    Serial.println(remaining_1);
  }

  //step_motor(M1);  // one-step testing (use debug=true in slot_machine.h)
  delay(4);
}
