/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    char* code = argv[1];
    char* command = argv[2];

    char* telegram = strcat(code, command);
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending telegram[%s]\n", telegram);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
        mySwitch.send(telegram);
	return 0;
}
