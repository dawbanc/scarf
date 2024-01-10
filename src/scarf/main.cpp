//----------------------------------------------------------------
// Project:                scarf
// Author:                 Dawson X Bancroft
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>
#include <cstring>

#include "scarf_logger.cpp"
#include "app_config.cpp"

int main(int argc, char* argv[]) {
	ScarfLogger logger("scarf");
	AppConfig app_config;	// create app configuration object

	// get command line args
	if (argc <= 1) {
		std::cout << "No arguments passed. In future versions, this may open the gui. Please check the CLI arguments:\n" << std::endl;
		app_config.printHelp();
		exit(1);
	} else {
		// parse cmd line args
		for (int i=1; i < argc; i++) {
			if ((strcmp(argv[i],"--h") == 0) || (strcmp(argv[i],"--help")==0)) {
				app_config.printHelp();
				exit(1);
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

	// initialize logger
	logger.setExtLogPath("/home/dxb/Documents/github/scarf/transcript");
	logger.enableExtLog();
	logger.openLog();
	logger.printProgramVersion();

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
