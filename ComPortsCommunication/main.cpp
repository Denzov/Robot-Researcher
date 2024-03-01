#include <iostream>

#define CE_SERIAL_IMPLEMENTATION
#include "comPortCommunication.h"

using namespace std;

int main()
{
	comPortCommunication port;
	port.init(3);
	string s = "LOL!";
	port.push_info("LOL!");
	port.take_feedback();
	std::cout<< "ANSWER: " << port.GetFeedback()<<'\n';	
}