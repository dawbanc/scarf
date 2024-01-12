//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <cstring>
#include <iostream>

#include "scarf_cli_args.cpp"
#include "scarf_logger.cpp"

int main(int argc, char *argv[]) {
	// construct Logger
	ScarfLogger logger("Scarf | RAW to CSV Converter");
	ScarfCLIArgs cli_args;

	// get command line args
	if (argc <= 1) {
	std::cout << "No arguments passed. In future versions, this may open the gui. Please check the CLI arguments:\n"
              << std::endl;
	exit(1);
	} else {
		// parse cmd line args
		for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-conf")) {

		} else if (strcmp(argv[i], "-debug") == 0) {

		} else if (strcmp(argv[i], "-dummy_run")) {

		} else if ((strcmp(argv[i], "--h") == 0) ||
					(strcmp(argv[i], "--help") == 0) ||
					(strcmp(argv[i], "-help") == 0) ||
					(strcmp(argv[i], "-h") == 0)) {

		} else if (strcmp(argv[i], "-int_log") == 0) {

		} else if (strcmp(argv[i], "-log") == 0) {

		} else if (strcmp(argv[i], "-no_log") == 0) {

		} else if (strcmp(argv[i], "-raw") == 0) {

		} else if (strcmp(argv[i], "-quiet") == 0) {

		} else {
		}
	}
  }

	// initialize logger
	logger.setExtLogPath("/home/dxb/Documents/github/scarf/scarf_log");	// dxb_dbg remove when correctly implemented
	logger.openLog();
	logger.printProgramVersion();

	// get sd configuration

	// write the titles of the

	// read sd card config blocks

	// read the data

	// read the sd card data block

	// write the sd card data block into file

	logger.closeLog();
	return 0;
}
