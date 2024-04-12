// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>

// You need to create an driver instance


#define RPLIDAR_MOTOR 2 // The PWM pin for control the speed of RPLIDAR's motor.
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
    void init() {

      //Serial.begin(9600);
      Serial2.begin(9600);
      lidar.begin(Serial3);

      pinMode(RPLIDAR_MOTOR, OUTPUT);
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 0);
      //Serial.println("YES");

      while (!IS_OK(lidar.waitPoint())) {
        analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
        // try to detect RPLIDAR...
        rplidar_response_device_info_t info;

        if (IS_OK(lidar.getDeviceInfo(info, 100))) {
          // detected...
          lidar.startScan();

          // start motor rotating at max allowed speed
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
    void transmit() {

      if (quality == 15) {
        data = "@" + String(distance, 2) + '|' + String(angle, 2);
        Serial2.print(data);
      }
      
    }
};
Transmitter transmitter;
void setup() {
  transmitter.init();
}

void loop() {


  transmitter.take_info();
  transmitter.transmit();
}
