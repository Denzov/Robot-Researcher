// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include "Transmitter.h"
#include "Receiver.h"

  Transmitter transmitter;
  Receiver receiver;

void setup() {
  //Serial.println("Motor test!");
  transmitter.init();
  receiver.init();
  // turn on motor
}

void loop() {
  /*uint8_t i;
  
  //Serial.print("tick");
  
  motor.run(FORWARD);
  motor.setSpeed(200);  */
  receiver.take_data();
  receiver.do_action();
  transmitter.take_info();
  transmitter.transmit();
}
