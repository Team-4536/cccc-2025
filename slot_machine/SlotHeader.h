const int SPR = 257; const int steps_per_revolution = SPR; // steps per revolution
const int debug = false;
int prevSegment[3] = {1, 1, 1};

const int wheel_items[3][5] = {
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5},
  {1, 2, 3, 4, 5}
};

int rand_pos(int motor, int &segment, bool isRandom = true) {
  static bool seeded = (randomSeed(millis()), true); // maybe not the best solution but it should work

  int position = random(0, 5); // get a random number from 0 to 4

  // rig game to win if desired
  if (!isRandom){
    position = 0;
  }
  
  segment = wheel_items[motor][position];  // Save the winning segment for display purposes
  float finalSegment = SPR * (2 + (2 * motor) + (position / 5.0) - ((prevSegment[motor]-1) / 5.0));   // calcualte target motor position in number of steps:
                                                                                                      // (3 full spins + extra per motor + additional segments - previous position) * SPR -> to convert 1-5 into steps for motor

  prevSegment[motor] = segment; // update previous for next spin
  return finalSegment;
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
