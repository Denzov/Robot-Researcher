#include "comPortCommunication.h"
#include <cstdint>

bool comPortCommunication::init(uint8_t port){
    com.SetPortName("\\\\.\\COM"+std::to_string(port));
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
        std::cout<<"[Warning] PORT WAS NOT OPEN.\n";
        #endif

        return 0;
    }
}

bool comPortCommunication::take_feedback(){
    buffer_char = com.ReadChar(successFlag);
    
    feedback.clear();
	while(successFlag)
	{
        std::cout<<buffer_char<<'\n';
		feedback += buffer_char;
		buffer_char = com.ReadChar(successFlag);	
	}
    return feedback.size() != 0;
}

std::string comPortCommunication::GetFeedback(){
    return feedback;
}