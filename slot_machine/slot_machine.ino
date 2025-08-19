#include "slot_machine.h"

int M1[4] = {2, 3, 4, 5}; // motor 1 pins
int M2[4] = {6, 7, 8, 9}; // motor 2 pins
int M3[4] = {10, 11, 12, 13}; // motor 3 pins

int button_pin = 16; // button input pin

int remaining_1 = 0;
int remaining_2 = 0;
int remaining_3 = 0;

int seg_1 = 1; // starting positions for all the wheels
int seg_2 = 1;
int seg_3 = 1;

bool resultPrinted = true; // tells the pi whether or not the result was printed to the serial monitor

//------------------------------------
// OPERATORS TO REMEMBER:
//   &&  -  "and"
//   ||  -  "or"
//   ==  -  "equal to"
//   !=  -  "not equal to"
//   >   -  "greater than"
//------------------------------------

//===========================

void setup() {
  Serial.begin();                      // serial monitor
  begin_motors(M1,M2,M3);              // motors
  pinMode(button_pin, INPUT_PULLDOWN); // button
}

//============================

void loop() {
  if (remaining_1 > 0) { // spins motor 1 if it has a remaining duration left
    step_motorM1(M1);
    remaining_1 = remaining_1 - 1;
  }else {
    stop_motor(M1);
  }

  if (remaining_2 > 0) { // spins motor 2 if it has a remaining duration left
    step_motorM2(M2);
    remaining_2 = remaining_2 - 1;
  }else {
    stop_motor(M2);
  }

  if (remaining_3 > 0) { // spins motor 3 if it has a remaining duration left
    step_motorM3(M3);
    remaining_3 = remaining_3 - 1;
  }else {
    stop_motor(M3);
  }
  

  // once all wheels have stopped spinning, this code runs
  if (remaining_1 == 0 && remaining_2 == 0 && remaining_3 == 0) {

    // checks if the computer has already printed the result, if it hasn't then it prints it
    if (resultPrinted == false){
      Serial.print("spin: ");  
      Serial.print(seg_1);
      Serial.print(seg_2);
      Serial.print(seg_3);

      if (seg_1 == 1 && seg_2 == 1 && seg_3 == 1) {                     // All three segments are 1 (starting position)
        Serial.println(", JACKPOT!!!!!");
      }else if (seg_1 == seg_2 && seg_2 == seg_3){                     // All three segments are the same
        Serial.println(", triple win!!!");
      }else if (seg_1 == seg_2 || seg_2 == seg_3 || seg_3 == seg_1) {  // Any two segments are the same
        Serial.println(", double win!!");
      }else {                                                          // None are the same
        Serial.println(". No luck, try again...");
      }

      resultPrinted = true; // prevents it from printing this over and over
    }


    // If the button is pressed, roll 3 spins. Otherwise do nothing and just wait
    if (digitalRead(button_pin) == HIGH) {
      // roll three new spins!
      remaining_1 = rand_pos(0, seg_1);  
      remaining_2 = rand_pos(1, seg_2);
      remaining_3 = rand_pos(2, seg_3);

      resultPrinted = false; // let the computer know the NEW result has not yet been printed
    }else { 
      delay(100);
    }
  }

  delay(4); // sets the speed of the steppers (smaller number = smaller delay between movments = faster overall speed)
}

//================================
