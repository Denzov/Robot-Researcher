#include <iostream>

#define CE_SERIAL_IMPLEMENTATION
#include "Communication.h"

using namespace std;

int main()
{
	Communication port;
	port.init(4);
	// string s = "101|5";
	// port.push_info(s.c_str());
	while(1){
		port.take_data();
	} 
}