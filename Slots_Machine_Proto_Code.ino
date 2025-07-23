const int M1[4] = {2, 3, 4, 5}; // Motor 1 pins
const int M2[4] = {6, 7, 8, 9}; // Motor 2 pins
const int M3[4] = {10, 11, 12, 13}; // Motor 3 pins

const int button_pin = 16; // Button input pin

const int SPR = 512; // Steps per revolution

int ticks = 0;
int current_step = 0;
int state = 0;

int end_pos_1;
int end_pos_2;
int end_pos_3;

int rand_pos() {
  // Returns a radom value from 512 to 1024 in increments of ~85
  return SPR * (random(0, 6) + 6) / 6;
}

void step_motor(const int pins[4]) {
  int position = current_step % 4;
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

  end_pos_1 = rand_pos(); end_pos_2 = rand_pos(); end_pos_3 = rand_pos();

  ticks = 0;
}

void loop() {
  switch (state) {
    case 0:
      step_motor(M1);
      step_motor(M2);
      step_motor(M3);
      if (++ticks >= end_pos_1) {
        ticks = 0;
        state = 1;
      }
      break;
    case 1:
      stop_motor(M1);
      step_motor(M2);
      step_motor(M3);
      if (++ticks >= end_pos_2) {
        ticks = 0;
        state = 2;
      }
      break;
    case 2:
      stop_motor(M1);
      stop_motor(M2);
      step_motor(M3);
      if (++ticks >= end_pos_3) {
        ticks = 0;
        state = 3;
      }
      break;
    case 3:
      stop_motor(M1);
      stop_motor(M2);
      stop_motor(M3);
      if (digitalRead(button_pin) == LOW) {
        ticks = 0;
        state = 0;
        end_pos_1 = rand_pos();
        end_pos_2 = rand_pos();
        end_pos_3 = rand_pos();
      }
      break;
  }

  current_step++;
  delay(2);
}
