#include <slots_machine.h>

const int M1[4] = {2, 3, 4, 5}; // motor 1 pins
const int M2[4] = {6, 7, 8, 9}; // motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // motor 3 pins

const int button_pin = 16; // button input pin

int state = 0;

int remaining_1;
int remaining_2;
int remaining_3;

void setup() {
  Serial.begin();

  for (int i = 0; i < 4; i++) {
    pinMode(M1[i], OUTPUT);
    pinMode(M2[i], OUTPUT);
    pinMode(M3[i], OUTPUT);
  }

  pinMode(button_pin, INPUT_PULLUP);

  // sets initial spin durations
  remaining_1 = rand_pos();
  remaining_2 = remaining_1 + rand_pos();
  remaining_3 = remaining_2 + rand_pos();
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
    return;
  } else {
    stop_motor(M3);
  }

  // waits for button to reset
  if (digitalRead(button_pin) == LOW) {
    // Ssts new spin durations
    remaining_1 = rand_pos();
    remaining_2 = remaining_1 + rand_pos();
    remaining_3 = remaining_2 + rand_pos();
  }

  state = ++state % 4;
  delay(2);
}
