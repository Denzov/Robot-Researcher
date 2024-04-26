#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_
// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>

// You need to create an driver instance


#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
// This pin should connected with the RPLIDAR's MOTOCTRL signal

class Transmitter {
  private:
    RPLidar lidar;
    String data;
    float distance;
    float angle;
    bool startBit;
    byte quality;

  public:
    Transmitter(){
      
    }
    void init() {
      lidar.begin(Serial3);

      pinMode(RPLIDAR_MOTOR, OUTPUT);
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 0);
      
      while (!IS_OK(lidar.waitPoint())) {
        analogWrite(RPLIDAR_MOTOR, 0); 
        rplidar_response_device_info_t info;

        if (IS_OK(lidar.getDeviceInfo(info, 100))) {
          lidar.startScan();
          analogWrite(RPLIDAR_MOTOR, 255);
          delay(1000);

        }
      }
    }

    void take_info() {
      if (IS_OK(lidar.waitPoint())) {
        distance = lidar.getCurrentPoint().distance; //distance value in mm unit
        angle    = lidar.getCurrentPoint().angle; //anglue value in degree
        startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
        quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
      }
    }

    void transmit(int8_t* nLetters) {

      if (quality == 15 && (*nLetters) < 15) {
        data =  String(distance, 2) + '|' + String(angle, 2) + "@";
        Serial2.print(data);
        (*nLetters)++;
      }
      else if((*nLetters) >= 15){
        Serial2.print("!");
      }
      
    }
};

#endif