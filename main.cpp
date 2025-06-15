/*
	SimpleBlog
	a minimal blog generator writen in c

*/
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include <iostream>

#include "config.h"

void printHelp(){

	std::cout << "simpleblog";
	std::cout << "\tVer: " << VERSION_STRING << '\n';
	std::cout << "USAGE: ./simpleblog <mode> <arguments>\n\n";
	std::cout << "Modes:\n";
	std::cout << "\thelp\t(display help)\n";  //std::cout << "\td\t(run as daemon with no output)\n"; std::cout << "\texport <dir>\t(export contacts to location)\n"; std::cout << "\tlist\t(list all loaded contacts)\n";


}





int main(int argc, char *argv[]){
	
	char *mode, *verb1, *verb2;
	/* parse arguments */
	switch (argc){
		case 1:
			std::cout << "No arguments provided: try simpleblog help.\n";
			break;
		case 2:
			mode = argv[1];
			break;
		case 3:
			mode = argv[1];
			verb1 = argv[2];
			break;
		case 4:
			mode = argv[1];
			verb1 = argv[2];
			verb2 = argv[3];
			break;

		default:
			std::cout << "Too many arguments provided, see simpleblog help\n";
			break;

	}
	if (strcmp(mode, "help") == 0){
		printHelp();
	}	





	return 0;
}
