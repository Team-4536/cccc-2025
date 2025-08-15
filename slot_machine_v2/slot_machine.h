const int SPR = 255; // steps per revolution
const int debug = false;

const int wheel_items[3][5] = {
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5}
};

int rand_pos(int motor, int &segment) {  // TODO: This doesn't take into account the current position of the wheel
  int position = random(0, 5); // get a number from 0 to 4
  segment = wheel_items[motor][position];
  return SPR * (2 + (position / 5.0) + 2 * motor);
  // return SPR;
}

void step_motor(const int pins[4], const int state) { // TODO: Embed State internally using a static int
  for (int i = 0; i < 4; i++)
    digitalWrite(pins[i], state == i || state == (i + 1) % 4);
}

void begin_all_motors(const int M1pins[4],const int M2pins[4],const int M3pins[4]) {
  for (int i = 0; i < 4; i++) {
    pinMode(M1pins[i], OUTPUT);
    pinMode(M2pins[i], OUTPUT);
    pinMode(M3pins[i], OUTPUT);
  }
}


void step_motorM1(const int pins[4]) {
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

void step_motorM2(const int pins[4]) {
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

void step_motorM3(const int pins[4]) {
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
