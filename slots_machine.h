const int SPR = 512; // Steps per revolution

int rand_pos() {
  // Returns a radom value from 512 to 1024 in increments of ~85
  return SPR * (random(0, 6) + 6) / 6;
}

void step_motor(const int pins[4], const int state) {
  digitalWrite(pins[0], state == 0 || state == 1);
  digitalWrite(pins[1], state == 1 || state == 2);
  digitalWrite(pins[2], state == 2 || state == 3);
  digitalWrite(pins[3], state == 3 || state == 0);
}

void stop_motor(const int pins[4]) {
  digitalWrite(pins[0], LOW);
  digitalWrite(pins[1], LOW);
  digitalWrite(pins[2], LOW);
  digitalWrite(pins[3], LOW);
}

randomSeed(analogRead(0));
