#include <iostream>
#include <cstring>

#include "app_config.cpp"

int main(int argc, char* argv[]) {
	
	// get command line args
	AppConfig app_config;	// create app configuration object
	app_config.printInfo(); // print scarf's information'

	if (argc <= 1) {
		std::cout << "No arguments passed. In future versions, this may open the gui. Please check the CLI arguments:\n" << std::endl;
		app_config.printHelp();
	} else {
		// parse cmd line args
		for (int i=1; i < argc; i++) {
			if ((strcmp(argv[i],"--h") == 0) || (strcmp(argv[i],"--help")==0)) {
				app_config.printHelp();
				return 1;
			} else if (strcmp(argv[i],"-debug") == 0) {
				app_config.debug = true;
			} else if (strcmp(argv[i], "-raw") == 0) {
				app_config.raw_file_location = argv[i+1];
				i++;
			} else {
					std::cout << "Default case (unrecognized option)\n" << std::endl;	
			}
		}	
	}

	// if debug is enabled print additional information
	if(app_config.debug == true) {
		std::cout << std::endl;
		app_config.printAppConfig();
	}

	// get sd configuration
	
	// write the titles of the 
	
	// read sd card config blocks
	
	// read the data
	
		// read the sd card data block

		// write the sd card data block into file
	
	return 0;
}
