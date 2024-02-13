#define DEBUG

#include <iostream>

#include "ceSerial.h"

class comPortCommunication{
private:
    bool successFlag;
    ceSerial com;
public:
    bool init();
    template<typename T> void push_info();

};