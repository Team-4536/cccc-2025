const int SPR = 513; // steps per revolution
const int debug = false;

const int wheel_items[3][5] = {
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5}
};

int rand_pos(int motor, int &segment) {
  int position = random(0, 5);
  segment = wheel_items[motor][position];
  return SPR * (2 + (position / 5.0) + 2 * motor);
  // return SPR;
}

void step_motor(const int pins[4], const int state) { // TODO: Embed State internally using a static int
  for (int i = 0; i < 4; i++)
    digitalWrite(pins[i], state == i || state == (i + 1) % 4);
}

void step_motor(const int pins[4]) {
  static int state = 0;

  state = state + 1;
  if (state >= 4) { // counts 0, 1, 2, 3
    state = 0;
  }

  if (debug) {Serial.print("Stepper State: ");}
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], state == i || state == (i + 1) % 4);
    if (debug) {Serial.print(state == i || state == (i + 1) % 4);  Serial.print(",");}
  }
  if (debug) {Serial.println(" ");}
}

void stop_motor(const int pins[4]) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], LOW);
  }
}
