#include "Transmitter.h"
#include "Receiver.h"

uint8_t nLetters = 0;

Transmitter transmitter;
Receiver receiver;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  

  receiver.init();
  transmitter.init();

  //Serial.print(1);
}

void loop() {
  // ML.run(FORWARD);
  // ML.setSpeed(255);
  //Serial.println();
  transmitter.take_info();
  transmitter.transmit(&nLetters);

  receiver.do_action();
  receiver.take_data(&nLetters);


  //receiver.test();

}
