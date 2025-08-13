#include "slot_machine.h"

const int M1[4] = {2, 3, 4, 5}; // motor 1 pins
const int M2[4] = {6, 7, 8, 9}; // motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // motor 3 pins

const int button_pin = 16; // button input pin

int state = 0;

int remaining_1 = 0;
int remaining_2 = 0;
int remaining_3 = 0;

int seg_1 = 1;
int seg_2 = 2;
int seg_3 = 3;

void setup() {
  Serial.begin();
  randomSeed(analogRead(0));

  for (int i = 0; i < 4; i++) {
    pinMode(M1[i], OUTPUT);te
    pinMode(M2[i], OUTPUT);
    pinMode(M3[i], OUTPUT);
  }

  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  if (remaining_1 > 0) { // spins motor 1 if it has a remaining duration left
    step_motor(M1, state);
    remaining_1--;
  } else {
    stop_motor(M1);
  }

  if (remaining_2 > 0) { // spins motor 2 if it has a remaining duration left
    step_motor(M2, state);
    remaining_2--;
  } else {
    stop_motor(M2);
  }

  if (remaining_3 > 0) { // spins motor 3 if it has a remaining duration left
    step_motor(M3, state);
    remaining_3--;
  } else {
    stop_motor(M3);

    Serial.print("spin:");  // TODO: Figure out why we're only spinning across 3 values instead of 5 values
    Serial.print(seg_1);
    Serial.print(seg_2);
    Serial.print(seg_3);

    if (seg_1 == seg_2 && seg_2 == seg_3) {
      Serial.println(", triple win!!!");
    } else if (seg_1 == seg_2 || seg_2 == seg_3 || seg_3 == seg_1) {
      Serial.println(", double win!!");
    } else {
      Serial.println(". No luck, try again...");
    }

    // waits for button to reset
    while (digitalRead(button_pin) == HIGH);  // TODO: Change button wiring, INPUT_PULLDOWN, and this logic to LOW
    
    // sets new spin durations
    remaining_1 = rand_pos(0, seg_1);  // TODO: Move random generator into main .ino file.  Also re-do logic so it spins N more spots, where N is random.
    remaining_2 = rand_pos(1, seg_2);
    remaining_3 = rand_pos(2, seg_3);
  }

  if (state == 3) { // counts 0, 1, 2, 3 (changed to be simpler logic for the camp participants)
    state = 0;
  } else {
    state = state + 1;
  }

  delay(4);
}
