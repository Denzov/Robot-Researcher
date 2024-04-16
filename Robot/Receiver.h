#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <AFMotor.h>


class Receiver{
private:
  char buffer_char;
  String buffer_str;
  uint8_t speed[2];
  MotorR motor(1);
  MotorL motor(2);
public:
  void take_data(){
    buffer_char = Serial2.;
    
    
    while(successFlag)
    {
          if(buffer_char == '@'){
              break;
          }
          feedback += buffer_char;
          buffer_char = com.ReadChar(successFlag);	
    }
      com.Delay(15);
  }
}

#endif