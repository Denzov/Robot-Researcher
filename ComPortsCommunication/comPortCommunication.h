#ifndef _COM_PORT_COMMUNICATION_H_
#define _COM_PORT_COMMUNICATION_H_

#define DEBUG

#include <iostream>
#include <string>
#include <cstdint>
#include "ceSerial.h"

class comPortCommunication{
private:
    ceSerial com;
    
    bool successFlag;
    
    char* s_data;   
    char buffer_char;
    std::string feedback;

public:
    bool init(uint8_t port);
    template<class T> void push_info(T data);
    bool take_feedback();
    std::string GetFeedback();
};

template<class T>
void comPortCommunication::push_info(T data){
    std::sprintf(s_data, "%s", data);
    successFlag = com.Write(s_data);
    com.Delay(3000);
    #ifdef DEBUG
    std::cout<<"[INFO] Write is " << ((successFlag) ? "" : "not ") << "correct\n";
    #endif
}

#endif