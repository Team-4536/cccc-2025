#include "slot_machine.h"

const int M1[4] = {2, 3, 4, 5}; // motor 1 pins
const int M2[4] = {6, 7, 8, 9}; // motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // motor 3 pins

const int button_pin = 16; // button input pin
const int led_pin = 15; // button input pin

int remaining_1 = 0;
int remaining_2 = 0;
int remaining_3 = 0;

int seg_1 = 1;
int seg_2 = 2;
int seg_3 = 3;

void setup() {
  randomSeed(millis());
  
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLDOWN);

  begin_motors(M1,M2,M3);
  Serial.begin();
}

void loop() {
  if (remaining_1 > 0) { // spins motor 1 if it has a remaining duration left
    step_motorM1(M1);
    remaining_1--;
  } else {
    stop_motor(M1);
  }

  if (remaining_2 > 0) { // spins motor 2 if it has a remaining duration left
    step_motorM2(M2);
    remaining_2--;
  } else {
    stop_motor(M2);
  }

  if (remaining_3 > 0) { // spins motor 3 if it has a remaining duration left
    step_motorM3(M3);
    remaining_3--;
  } else {
    stop_motor(M3);
  }

  if (remaining_1 <= 0 && remaining_2 <= 0 && remaining_3 <= 0) {
    Serial.print("spin:");  // TODO: Figure out why we're only spinning across 3 values instead of 5 values
    Serial.print(seg_1);
    Serial.print(seg_2);
    Serial.print(seg_3);

    if (seg_1 == seg_2 && seg_2 == seg_3) {
      Serial.println(", triple win!!!");
      digitalWrite(led_pin,HIGH);
    } else if (seg_1 == seg_2 || seg_2 == seg_3 || seg_3 == seg_1) {
      Serial.println(", double win!!");
      digitalWrite(led_pin,HIGH);
    } else {
      Serial.println(". No luck, try again...");
      digitalWrite(led_pin,LOW);
    }

     // Do nothing and wait until the button is pressed.
    if (digitalRead(button_pin) == LOW) {  
      delay(100); 
    } else { 
      // roll three new spins!
      remaining_1 = rand_pos(0, seg_1);
      remaining_2 = rand_pos(1, seg_2);
      remaining_3 = rand_pos(2, seg_3);
    }
  }

  delay(4);
}
