const int SPR = 255; // steps per revolution
const int debug = false;

const int wheel_items[3][5] = {
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5}
};


int rand_pos(int motor, int &segment) {  // TODO: This doesn't take into account the current position of the wheel
  randomSeed(millis());

  int position = random(0, 5); // get a number from 0 to 4
  segment = wheel_items[motor][position];  // Save the winning segment for display purposes
  return SPR * (2 + (position / 5.0) + 2 * motor);  // return target motor position in number of steps
}

void begin_motors(const int pinsM1[4],const int pinsM2[4],const int pinsM3[4]) {
  for (int i = 0; i < 4; i++) {
    pinMode(pinsM1[i], OUTPUT);
    pinMode(pinsM2[i], OUTPUT);
    pinMode(pinsM3[i], OUTPUT);
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


void step_motor(const int pins[4], const int state) { // TODO: Embed State internally using a static int
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], state == i || state == (i + 1) % 4);
  }
}
