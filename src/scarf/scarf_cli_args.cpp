//----------------------------------------------------------------
// Project:                scarf
// Author:                 Dawson X Bancroft
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>

class ScarfCLIArgs {
    private:
        std::string conf_path;                      // -conf <path>
        bool debug = false;                         // -debug
        bool help = false;                          // --help | --h | -help | -h
        std::string ext_log_path = "scarf_log";     // -log <path> (default is scarf_log)
        std::string int_log_path = "null";          // -int_log <path>
        std::string raw_file_path = "null";         // -raw
        bool quiet = false;                         // - quiet


    public:
        void setConfPath(std::string input_conf_path);
        std::string getConfPath(void);
};

void ScarfCLIArgs::setConfPath(std::string input_conf_path){
    conf_path = input_conf_path;
}

std::string ScarfCLIArgs::getConfPath(void){
    return conf_path;
}

