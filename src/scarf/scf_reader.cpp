//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/23
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <filesystem>
#include <iostream>

class ScfReader{

    private:

    public:
        ScarfLogger* logger;
        void readScfFile(std::string scf_file_path);

};



void ScfReader::readScfFile(std::string scf_file_path){
    // check to see if file exists
    logger->printMessage("ScfReader starting...\n", false, true, false);
    if (!std::filesystem::exists(scf_file_path)){
        logger->printError('F', 2, "The file path specified by \"-conf\" does not exist.", true, true, true);
    }

    // read in the lines
    std::ifstream config_file;
    config_file.open(scf_file_path);
    std::string scf_line;
    if (config_file.is_open()) {
        while(config_file) {
            std::getline(config_file, scf_line);
            logger->printMessage("ScfReader read: " + scf_line, false, true, false);
        }
    }


}
