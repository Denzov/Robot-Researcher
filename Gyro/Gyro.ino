#include <DFRobot_BMI160.h>
#define AcX
#define AcY 

struct vec2 {
  float x, y;
};

class Gyro {
  private:
    DFRobot_BMI160 bmi160;
    const int8_t i2c_addr = 0x68;
    int16_t accelGyro[6] = {0};
    float result;
    float dt;
    float angle = 0;
    float current_millis = 0, last_millis;
    vec2 S = {};
    vec2 V = {};

    vec2 base_acceleration = {};

  public:
    void init() {
      if (bmi160.softReset() != BMI160_OK) {
        Serial.println("reset false");
        while (1);
      }

      //set and init the bmi160 i2c address
      if (bmi160.I2cInit(i2c_addr) != BMI160_OK) {
        Serial.println("init false");
        while (1);
      }
      
      bmi160.getAccelGyroData(accelGyro);
      base_acceleration = {accelGyro[3], accelGyro[4]};
    }
    void calc() {
      if (!bmi160.getAccelGyroData(accelGyro)) {
        current_millis = millis();
        dt = (current_millis - last_millis)*0.001;
#ifdef ANG
        result = accelGyro[2] * 0.061 * dt;
        if (abs(result) >= 0.1) {
          angle += result;
        }
#endif
#ifdef AcX
        result = (accelGyro[3]- base_acceleration.x)/16384.f*9.805;
        if (abs(result) >= 1){
          V.x += result * dt;
          S.x += result * dt *dt * 0.5;
        }
#endif        
#ifdef AcY
        result = (accelGyro[4]- base_acceleration.y)/16384.f*9.805;
        if (abs(result) >= 1){
          V.y += result * dt;
          S.y += result * dt *dt * 0.5;
        }
#endif            
        last_millis = current_millis;
      }
    }
    float get_angle() {
      return angle;
    }
    
    float get_vx() {
      return V.x;
    }
    float get_vy() {
      return V.y;
    }
    float get_x() {
      return S.x;
    }
    float get_y() {
      return S.y;
    }

};


Gyro gyro;
void setup() {
  Serial.begin(115200);
  gyro.init();
}

void loop() {
  gyro.calc();
  Serial.print("x -- \t");
  Serial.println(gyro.get_vx());
  Serial.print("y -- \t");
  Serial.println(gyro.get_vy());
  Serial.println();
}
