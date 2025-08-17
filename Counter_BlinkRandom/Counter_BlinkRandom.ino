int led_pin = LED_BUILTIN;
int button_pin = 15;

int counter = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  counter = counter - 1;
  Serial.println(counter);

  if(counter<=0) {
    counter = random(2, 8); // roll a number from 2 to 7;
    Serial.print("New Counter: ");
    Serial.println(counter);
  }

  if (counter > 2) {
    digitalWrite(led_pin, HIGH);  // turn the LED on (HIGH is the voltage level)    
  } else {
    digitalWrite(led_pin,LOW);  // turn the LED off by making the voltage LOW
  }

  delay(250);                      // wait for 250 milliseconds!
}
