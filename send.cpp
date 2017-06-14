/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

void help() {
	printf("send [-P port] [-p protocol] [-n repeat] [-t type] [Type 1:RawTelegram]/[Type 2: SystemCode UnitCode Command]\n");
}

int main(int argc, char *argv[]) {
    int PIN = 0;
    int repeat = 10;
    int protocol = 1;
    int type = 1;
    int c;

	if (argc == 1) {
		help();
		return 1;
	}

    while ((c = getopt (argc, argv, "P:n:p:t:h")) != -1) {
	switch(c) {
		printf("%c\n",c);
		case 'P':
			PIN = atoi(optarg);
			break;
		case 'n':
			repeat = atoi(optarg);
			break;
		case 'p':
			protocol = atoi(optarg);
			break;
		case 't':
                        type = atoi(optarg);
                        break;
		case 'h':
			help();
			return 0;
	}
    }


    
    if (wiringPiSetup () == -1) return 1;
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
	mySwitch.setProtocol(protocol);
	mySwitch.setRepeatTransmit(repeat);
	
	if (type == 1) {
    		char* telegram = (char*)malloc(sizeof(char));

    		for (int i = optind; i < argc; i++) {
                	telegram = strcat(telegram, argv[i]);
		}
		printf("sending telegram[%s]\n", telegram);
		mySwitch.send(telegram);
	}

	else if (type == 2) {
		char* systemCode = argv[optind++];
    		int unitCode = atoi(argv[optind++]);
    		int command  = atoi(argv[optind++]);
		switch(command) {
        		case 1:
				printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
            			mySwitch.switchOn(systemCode, unitCode);
            			break;
        		case 0:
				printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);
            			mySwitch.switchOff(systemCode, unitCode);
            			break;
        		default:
            			printf("command[%i] is unsupported\n", command);
            			return -1;
    		}
    	}
    	return 0;
}
