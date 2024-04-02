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
		std::cout<<"[INFO] Was open port " << com.GetPort().c_str() << '\n';
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
		if(buffer_char != '@'){
            feedback += buffer_char;
            buffer_char = com.ReadChar(successFlag);	

        }
        else{
            break;
        }

        
	}
    //com.Delay(1000);
    return feedback.size() != 0;
}

std::string comPortCommunication::GetFeedback(){
    return feedback;
}

void comPortCommunication::transform_info(){
    buffer_str.clear();
    number_of_stick = 0;
    for(uint8_t i = 0; i < feedback.size(); i++){
        if(feedback[i] != '|'){
            continue;
        }
        else{
            number_of_stick = i;
        }
        if(feedback.size() - 1 != i){
            continue;
        }

        if(number_of_stick == i){
            buffer_str.resize(number_of_stick - 1);
            for (uint8_t i = 0; i < number_of_stick - 1; i++)
            {
                buffer_str[i] = feedback[i];
            }
            
        }
    }
    


}
