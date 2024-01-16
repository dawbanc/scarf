//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <cstring>
#include <string>

#include "scarf_cli_args.cpp"
#include "scarf_logger.cpp"

int main(int argc, char *argv[]) {
  // construct Logger
  ScarfLogger logger("Scarf | RAW to CSV Converter");
  ScarfCLIArgs cli_args;

  // get command line args
  std::string unrecognized_args[64];
  int unrecognized_args_cnt = 0;
  if (argc <= 1) {
    logger.printError('F', 0, "There were no command line arguments specified. In the future this may automatically open the GUI, but as of right now it will quit.", true, false, false);
    exit(1);
  } else {
    // parse cmd line args
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-conf")) {
        cli_args.setConfPath(argv[i+1]);
        i++;
      } else if (strcmp(argv[i], "-debug") == 0) {
        cli_args.setDebug(true);
      } else if (strcmp(argv[i], "-dummy_run")) {
        cli_args.setDummyRun(true);
      } else if ((strcmp(argv[i], "--h") == 0) ||
                 (strcmp(argv[i], "--help") == 0) ||
                 (strcmp(argv[i], "-help") == 0) ||
                 (strcmp(argv[i], "-h") == 0)) {
        cli_args.setHelp(true);
      } else if (strcmp(argv[i], "-int_log") == 0) {
        cli_args.setIntLogPath(argv[i+1]);
        i++;
      } else if (strcmp(argv[i], "-log") == 0) {
        cli_args.setExtLogPath(argv[i+1]);
        i++;
      } else if (strcmp(argv[i], "-no_log") == 0) {
        cli_args.setNoLog(true);
      } else if (strcmp(argv[i], "-raw") == 0) {
        cli_args.setRawFilePath(argv[i+1]);
        i++;
      } else if (strcmp(argv[i], "-quiet") == 0) {
        cli_args.setQuiet(true);
      } else {
        unrecognized_args[unrecognized_args_cnt] = argv[i];
        logger.printError('E', 1, "unrecognized arguments detected: " + std::string(argv[i]), true, false, false);
        unrecognized_args_cnt++;
      }
    }
  }

  // initialize logger
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
