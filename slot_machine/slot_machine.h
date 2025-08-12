const int SPR = 512; // steps per revolution

const int wheel_items[3][5] = {
  {0, 0, 1, 1, 2},
  {0, 1, 1, 2, 3},
  {0, 0, 0, 1, 2}
};

int rand_pos(int motor, int &segment) {
  int position = random(0, 5);
  segment = wheel_items[motor][position];
  return SPR * (2 + (position / 5.0) + 2 * motor);
  // return SPR;
}

void step_motor(const int pins[4], const int state) {
  for (int i = 0; i < 4; i++) digitalWrite(pins[i], state == i || state == (i + 1) % 4);
}

void stop_motor(const int pins[4]) {
  for (int i = 0; i < 4; i++) digitalWrite(pins[i], LOW);
}
