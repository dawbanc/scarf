//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/23
// Notes:
// For changes view git history
//----------------------------------------------------------------
class ScfReader{

    private:

    public:
        ScarfLogger* logger;
        ScfReader(void);
        void testLogger(void);
};

ScfReader::ScfReader(void){

}
//void ScfReader::setLogger(ScarfLogger)

void ScfReader::testLogger(void){
    logger->printMessage("Test logger from scfReader", true, true, true);
}
