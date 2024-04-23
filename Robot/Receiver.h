#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <AFMotor.h>
#include "Gyro.h"

enum Action : uint8_t {
  NEW = 1,
  A_FORWARD,
  A_BACK,
  A_TURN_LEFT,
  A_TURN_RIGHT,
  A_STOP
};

class Receiver {
private:
  AF_DCMotor MotorR = AF_DCMotor(1);
  AF_DCMotor MotorL = AF_DCMotor(2);
  Gyro gyro;
  char buffer_char;
  bool actionIsCompleted = 0;

  float current_millis = 0, last_millis = 0, delta_time = 3000;
  float angle = 0;

  Action action = A_STOP;
  uint8_t speed[2];
  const int16_t SPEED = 200;

public:
  void init() {

    //gyro.init();
   // while(action != NEW){
  //    if(Serial2.available()) action = atoi(Serial2.readString().c_str());
      //Serial.println(action);
   // }
  }
  void take_data() {

    //actionIsCompleted = 0;

      
      if(Serial2.available()) 
      {
        action = atoi(Serial2.readString().c_str());
        Serial.println(action);
      }

  }
  void do_action() {
    //gyro.calc();
    //Serial.println(actionIsCompleted);
    if(action == NEW){
      last_millis = millis();
      actionIsCompleted = 0; 
    }
    if (!actionIsCompleted) {
      switch (action) {
        case A_FORWARD:
          //Serial.println("FORWARD");
          current_millis = millis();
          if(current_millis - last_millis > delta_time) {
            last_millis = current_millis;
            actionIsCompleted = 1;
            
            break;
          }
          //Serial.print(2);
          MotorR.run(FORWARD);
          MotorL.run(FORWARD);
          MotorR.setSpeed(SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_BACK:
          current_millis = millis();
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
          MotorR.run(BACKWARD);
          MotorL.run(FORWARD);
          MotorR.setSpeed(SPEED);
          MotorL.setSpeed(SPEED);
          break;
        case A_TURN_LEFT:
          MotorR.run(FORWARD);
          MotorL.run(BACKWARD);
          MotorR.setSpeed(SPEED);
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