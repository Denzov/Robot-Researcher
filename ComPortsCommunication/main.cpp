#include <iostream>

#define CE_SERIAL_IMPLEMENTATION
#include "comPortCommunication.h"

using namespace std;

int main()
{
	comPortCommunication port;
	port.init(3);
	// string s = "101|5";
	// port.push_info(s.c_str());
	while(1){
		port.take_feedback();
		std::cout<< port.GetFeedback();	
		std::cout<< "\n";

	} 
}