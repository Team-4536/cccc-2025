//
// Hello world, microcontroller style!
// This program will make the Pico say hello to the world
//

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Hello World!");
  delay(1000);
}
