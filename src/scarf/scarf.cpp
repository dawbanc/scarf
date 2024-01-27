//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "scarf.h"

int main(int argc, char *argv[]) {
  // construct Logger
  ScarfLogger logger("scarf");
  ScarfCLIArgs cli_args;

  // get command line args
  std::string unrecognized_args[64];
  int unrecognized_args_cnt = 0;
  //logger.printMessage("argc = " + std::to_string(argc), true, false, false); //dxb_dbg
  if (argc <= 1) {
    logger.printError('F', 0, "There were no command line arguments specified. In the future this may automatically open the GUI, but as of right now it will quit.", true, false, false);
    exit(1);
  } else {
    // parse cmd line args
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-conf") == 0) {
        cli_args.setConfPath(argv[i+1]);
        i++;
      } else if (strcmp(argv[i], "-debug") == 0) {
        cli_args.setDebug(true);
      } else if (strcmp(argv[i], "-dummy_run") == 0) {
        cli_args.setDummyRun(true);
        cli_args.setDebug(true);
        cli_args.setConfPath("config/debug_simple.scf");
        cli_args.setIntLogPath("scarf_debug");
        cli_args.setRawFilePath("simple.raw");
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
        logger.printError('E', 1, "unrecognized arguments detected: " + std::string(argv[i]) + " . Program will continue.", true, false, false);
        unrecognized_args_cnt++;
      }
    }
  }


  // initialize logger
  (cli_args.getQuiet()) ? logger.setEnableTerLog(false) : logger.setEnableTerLog(true);               // if quiet turn off terminal output
  (cli_args.getIntLogPath() == "null") ? logger.setEnableIntLog(false) : logger.setEnableIntLog(true), logger.setIntLogPath(cli_args.getIntLogPath());                                                      // if internal log path isnt set dont enable it
  if (cli_args.getExtLogPath() == "null") {
    if (cli_args.getNoLog()) {
      logger.setEnableExtLog(false);
    } else {
      logger.setExtLogPath("scarf_log");
      logger.setEnableExtLog(true);
    }
  } else {
    logger.setExtLogPath(cli_args.getExtLogPath());
    logger.setEnableExtLog(true);
  }
  logger.openLog();
  logger.printMessage("Initiating logger...\n", false, true, false);
  logger.printProgramVersion();
  if (cli_args.getDebug()){
    logger.printLineToAll(cli_args.toString()); // if debug is enabled, show the cli config
  }
  logger.printMessage("Logger Initiated.\n", false, true, false);

  // get sd configuration
  ScfReader* scf_reader = new ScfReader();
  scf_reader->logger = &logger;
  scf_reader->readScfFile(cli_args.getConfPath());

  // write the titles of the

  // read sd card config blocks

  // read the data

  // read the sd card data block

  // write the sd card data block into file

  logger.closeLog();
  return 0;
}
