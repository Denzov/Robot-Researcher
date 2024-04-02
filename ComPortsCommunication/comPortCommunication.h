#ifndef _COM_PORT_COMMUNICATION_H_
#define _COM_PORT_COMMUNICATION_H_

#define DEBUG

#include <iostream>
#include <string>
#include <cstdint>
#include "ceSerial.h"

class comPortCommunication
{
private:
    ceSerial com;

    bool successFlag;
    bool number_of_data = 0;

    char *s_data;
    char buffer_char;
    std::string buffer_str; 
    std::string feedback;

    float data[2];
    uint8_t number_of_stick;

public:
    
    bool init(uint8_t port);
    bool take_feedback();
    void transform_info();
    template <class T>
    void push_info(T data);
    
    std::string GetFeedback();
};

template <class T>
void comPortCommunication::push_info(T data)
{
    std::sprintf(s_data, "%s", data);
    successFlag = com.Write(s_data, strlen(s_data) + 1);
    com.Delay(3000);
#ifdef DEBUG
    std::cout << "[INFO] Write is " << ((successFlag) ? "" : "not ") << "correct\n";
#endif //DEBUG
}

#endif //_COM_PORT_COMMUNICATION_H_