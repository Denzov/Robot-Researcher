// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include "Transmitter.h"



Transmitter transmitter;
void setup() {
  //Serial.println("Motor test!");
  transmitter.init();
  // turn on motor
}

void loop() {
  /*uint8_t i;
  
  //Serial.print("tick");
  
  motor.run(FORWARD);
  motor.setSpeed(200);  */
  transmitter.take_info();
  transmitter.transmit();
  
}
