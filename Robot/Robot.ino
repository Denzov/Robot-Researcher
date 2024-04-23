// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include "Transmitter.h"
#include "Receiver.h"

  Transmitter transmitter;
  Receiver receiver;
  
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
      
  //Serial.println("Motor test!");
  receiver.init();
  transmitter.init();
  
  
  // turn on motor
}

void loop() {
  /*uint8_t i;
  
  //Serial.print("tick");*/
  

 
  transmitter.take_info();
  transmitter.transmit();
  receiver.take_data();
  receiver.do_action();
}
