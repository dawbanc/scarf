//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/23
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "scarf_logger.cpp"

class ScfReader{

    template <class logger>

    //private:

    public:
        ScfReader(logger& logger_in);
        void testLogger(void);
};

ScfReader::ScfReader(logger& logger_in){
    logger = logger_in;
}

void ScfReader::testLogger(void){
    logger.printMessage("Test logger from scfReader", true, true, true);
}
