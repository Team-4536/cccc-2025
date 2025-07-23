const int M1[4] = {2, 3, 4, 5}; // Motor 1 pins
const int M2[4] = {6, 7, 8, 9}; // Motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // Motor 3 pins

const int button_pin = 16; // Button input pin

const int SPR = 512; // Steps per revolution

int current_step = 0;

int remaining_1;
int remaining_2;
int remaining_3;

int rand_pos() {
  // Returns a radom value from 512 to 1024 in increments of ~85
  return SPR * (random(0, 6) + 6) / 6;
}

void step_motor(const int pins[4]) {
  digitalWrite(pins[0], position == 0 || position == 1);
  digitalWrite(pins[1], position == 1 || position == 2);
  digitalWrite(pins[2], position == 2 || position == 3);
  digitalWrite(pins[3], position == 3 || position == 0);
}

void stop_motor(const int pins[4]) {
  digitalWrite(pins[0], LOW);
  digitalWrite(pins[1], LOW);
  digitalWrite(pins[2], LOW);
  digitalWrite(pins[3], LOW);
}

void setup() {
  Serial.begin();
  randomSeed(analogRead(0));

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
    step_motor(M1);
    remaining_1--;
  } else {
    stop_motor(M1);
  }

  if (remaining_2 > 0) { // spins motor 1 if it has a remaining duration left
    step_motor(M2);
    remaining_2--;
  } else {
    stop_motor(M2);
  }

  if (remaining_3 > 0) { // spins motor 1 if it has a remaining duration left
    step_motor(M3);
    remaining_3--;
    return;
  } else {
    stop_motor(M3);
  }

  // waits for button to reset
  if (digitalRead(button_pin) == LOW) {
    // set new spin durations
    remaining_1 = rand_pos();
    remaining_2 = remaining_1 + rand_pos();
    remaining_3 = remaining_2 + rand_pos();
  }

  current_step = ++current_step % 4;
  delay(2);
}
