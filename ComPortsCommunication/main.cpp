// File: test.cpp
// Description: Serial (Com port) console program for Windows and Linux
// WebSite: http://cool-emerald.blogspot.sg/2017/05/serial-port-programming-in-c-with.html
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

#include <stdio.h>
#define CE_SERIAL_IMPLEMENTATION
#include "ceSerial.h"
using namespace std;

int main()
{
	ceSerial com("\\\\.\\COM3",9600,8,'N',1); // Windows

	printf("Opening port %s.\n",com.GetPort().c_str());
	if (com.Open() == 0) {
		printf("OK.\n");
	}
	else {
		printf("Error.\n");
		return 1;
	}

	bool successFlag;
	printf("Writing.\n");
	char s[]="KEK!";
	successFlag=com.Write(s); // write string
//	successFlag=com.WriteChar('!'); // write a character
	printf("Waiting 3 seconds.\n");
	ceSerial::Delay(3000); // delay to wait for a character

	printf("Reading.\n");
	char c=com.ReadChar(successFlag); // read a char
	if(successFlag) printf("Rx: %c\n",c);
    else printf("Not read.\n");

	printf("Closing port %s.\n", com.GetPort().c_str());
	com.Close();
	return 0;
}