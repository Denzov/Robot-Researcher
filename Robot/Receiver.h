#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <AFMotor.h>
#include "Gyro.h"

enum Action : uint8_t {
  A_FORWARD = 1,
  A_BACK,
  A_TURN_LEFT,
  A_TURN_RIGHT,
  A_STOP
};

class Receiver {
private:
  AF_DCMotor MotorR = {1};
  AF_DCMotor MotorL = {2};
  Gyro gyro;
  char buffer_char;
  bool actionIsCompleted = 0;

  float current_millis = 0, last_millis = 0, delta_time = 10000;
  float angle = 0;

  Action action = A_STOP;
  uint8_t speed[2];
  const int16_t SPEED = 100;

public:
  void init() {
    //gyro.init();
    Serial.begin(9600);
    Serial2.begin(9600);
  }
  void take_data() {

    //actionIsCompleted = 0;

    
      buffer_char = Serial2.read();
      Serial.println(buffer_char);
    
  }
  void do_action() {
    //gyro.calc();
    if (!actionIsCompleted) {
      switch (action) {
        case A_FORWARD:
          current_millis = millis();
          if (current_millis - last_millis > delta_time) {
            last_millis = current_millis;
            actionIsCompleted = 1;
            break;
          }
          MotorR.run(FORWARD);
          MotorL.run(FORWARD);
          MotorR.setSpeed(SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_BACK:
          if (current_millis - last_millis > delta_time) {
            last_millis = current_millis;
            actionIsCompleted = 1;
            break;
          }
          MotorR.run(BACKWARD);
          MotorL.run(BACKWARD);
          MotorR.setSpeed(SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_TURN_RIGHT:
          MotorR.setSpeed(-SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_TURN_LEFT:
          MotorR.setSpeed(-SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_STOP:
          actionIsCompleted = 1;
          break;
      }

    } else {
      MotorR.setSpeed(0);
      MotorL.setSpeed(0);
    }
  }
};

#endif