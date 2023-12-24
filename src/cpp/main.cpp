#include <iostream>
#include <cstring>

#include "app_config.h"

int main(int argc, char* argv[]) {
	
	// get command line args
	for (int i=1; i < argc; i++) {
		std::cout << "Args: " << argv[i] << std::endl;
	}
	if (argc <= 1) {
		std::cout << "No arguments passed. In future versions, this may open the gui.\n" << std::endl;
	} else {
		// parse cmd line args
		for (int i=1; i < argc-1; i++) {
			if ((strcmp(argv[i],"--h") == 0) || (strcmp(argv[i],"--help")==0)) {
					std::cout << "Help call\n" << std::endl;
			} else {
					std::cout << "Default case (unrecognized option)\n" << std::endl;	
			}
		}	
	}


	// get sd configuration
	
	// write the titles of the 
	
	// read sd card config blocks
	
	// read the data
	
		// read the sd card data block

		// write the sd card data block into file
	
	std::cout << "Test\n";
	return 0;
}
