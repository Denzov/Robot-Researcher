#include "comPortCommunication.h"

bool comPortCommunication::init(){

    com.SetPortName("\\\\.\\COM3");
    com.SetBaudRate(9600);
	com.SetDataSize(8);
	com.SetParity('N');
	com.SetStopBits(1);
	
    if (com.Open() == 0) {

        #ifdef DEBUG
		std::cout<<"[INFO] Was open port %s.\n" << com.GetPort().c_str() << '\n';
        #endif
        return 1;
	}
    else{
        #ifdef DEBUG
        std::cout<<"[Error] PORT WAS NOT OPEN.\n";
        #endif

        return 0;
    }
}
template<typename T>
void comPortCommunication::push_info(){
    
    
}