#include "Communication.h"
#include <cstdint>

bool Communication::init(uint8_t port){
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

void Communication::take_feedback(){
    buffer_char = com.ReadChar(successFlag);
    feedback.clear();    
    
	while(successFlag)
	{
        if(buffer_char == '@'){
            break;
        }
        feedback += buffer_char;
        buffer_char = com.ReadChar(successFlag);	
	}
    com.Delay(10);
}

void Communication::transform_info(){
    buffer_str.resize(number_of_stick);
    for (uint8_t i = 0; i < number_of_stick; i++)
    {
        buffer_str[i] = feedback[i];
    }
    data[0] = std::stof(buffer_str);
    
    buffer_str.resize(feedback.size() - number_of_stick);
    for (uint8_t i = 0; i < feedback.size() - number_of_stick; i++)
    {
        buffer_str[i] = feedback[number_of_stick + i + 1];
    }
    data[1] = std::stof(buffer_str);
    
}

std::string Communication::GetFeedback(){
    return feedback;
}

bool Communication::infoIsCorrect(){
    value_correct_sym = 0;
    for(uint8_t i = 0; i < feedback.size(); i++){
        if(feedback[i] == '.'){
            value_correct_sym++;
        }
        else if(feedback[i] == '|'){
            number_of_stick = i;
            value_correct_sym++;
        }
    }
    return value_correct_sym == 3;
}

void Communication::print_data(){
    std::cout<< "Distance:\t" << data[0] << "\t\tAngle:\t" << data[1] << '\n';
}

void Communication::take_data(){
    take_feedback();
	if(infoIsCorrect()){
	    transform_info();
		//print_data();
	}
}

float Communication::GetDistance(){
    return data[0];
}

float Communication::GetAngle(){
    return data[1];
}

/*void Communication::push_info(){
    
}*/