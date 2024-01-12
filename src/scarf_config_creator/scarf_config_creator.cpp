//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>

#include "scarf_logger.cpp"

int main(int argc, char* argvp[]){
    ScarfLogger logger("scc (Scarf Configuration Creator)");


    logger.setExtLogPath("/home/dxb/Documents/github/scarf/scc_log");	// dxb_dbg remove when correctly implemented
    logger.openLog();
    logger.printProgramVersion();


    logger.closeLog();
    return 0;
}
