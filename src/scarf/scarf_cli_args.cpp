//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        23/12/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>

class ScarfCLIArgs {
    private:
        std::string conf_path;                      // -conf <path>
        bool debug = false;                         // -debug
        bool dummy_run = false;                     // -dummy_run
        bool help = false;                          // --help | --h | -help | -h
        std::string int_log_path = "null";          // -int_log <path>
        std::string ext_log_path = "null";     // -log <path> (default is scarf_log)
        bool no_log = false;
        std::string raw_file_path = "null";         // -raw
        bool quiet = false;                         // -quiet


    public:
        void setConfPath(std::string input_conf_path);
        std::string getConfPath(void);

        void setDebug(bool input_debug);
        bool getDebug(void);

        void setDummyRun(bool input_dummy_run);
        bool getDummyRun(void);

        void setHelp(bool input_help);
        bool getHelp(void);

        void setIntLogPath(std::string input_int_log_path);
        std::string getIntLogPath(void);

        void setExtLogPath(std::string input_ext_log_path);
        std::string getExtLogPath(void);

        void setRawFilePath(std::string input_raw_file_path);
        std::string getRawFilePath(void);

        void setNoLog(bool input_no_log);
        bool getNoLog(void);

        void setQuiet(bool input_quiet);
        bool getQuiet(void);

        std::string boolToString(bool input_bool);
        std::string toString(void);
};

void ScarfCLIArgs::setConfPath(std::string input_conf_path){
    conf_path = input_conf_path;
}

std::string ScarfCLIArgs::getConfPath(void){
    return conf_path;
}

void ScarfCLIArgs::setDebug(bool input_debug){
    debug = input_debug;
}

bool ScarfCLIArgs::getDebug(void){
    return debug;
}

void ScarfCLIArgs::setDummyRun(bool input_dummy_run){
    dummy_run = input_dummy_run;
}

bool ScarfCLIArgs::getDummyRun(void){
    return dummy_run;
}

void ScarfCLIArgs::setHelp(bool input_help){
    help = input_help;
}

bool ScarfCLIArgs::getHelp(void){
    return help;
}

void ScarfCLIArgs::setIntLogPath(std::string input_int_log_path){
    int_log_path = input_int_log_path;
}

std::string ScarfCLIArgs::getIntLogPath(void){
    return int_log_path;
}

void ScarfCLIArgs::setExtLogPath(std::string input_ext_log_path){
    ext_log_path = input_ext_log_path;
}

std::string ScarfCLIArgs::getExtLogPath(void){
    return ext_log_path;
}

void ScarfCLIArgs::setRawFilePath(std::string input_raw_file_path){
    raw_file_path = input_raw_file_path;
}

std::string ScarfCLIArgs::getRawFilePath(void){
    return raw_file_path;
}

void ScarfCLIArgs::setNoLog(bool input_no_log){
    no_log = input_no_log;
}

bool ScarfCLIArgs::getNoLog(void){
    return no_log;
}

void ScarfCLIArgs::setQuiet(bool input_quiet){
    quiet = input_quiet;
}

bool ScarfCLIArgs::getQuiet(void){
    return quiet;
}

std::string ScarfCLIArgs::boolToString(bool input_bool){
    if (input_bool){
        return "true";
    } else {
        return "false";
    }
}

std::string ScarfCLIArgs::toString(void){
    std::string temp;
    temp.append("CLI Argument Configuration:\n");
    temp.append("-conf:     \t");
    temp.append(getConfPath());
    temp.append("\n");
    temp.append("-debug:    \t");
    temp.append(boolToString(getDebug()));
    temp.append("\n");
    temp.append("-dummy_run:\t");
    temp.append(boolToString(getDummyRun()));
    temp.append("\n");
    temp.append("-help:     \t");
    temp.append(boolToString(getHelp()));
    temp.append("\n");
    temp.append("-int_log:  \t");
    temp.append(getIntLogPath());
    temp.append("\n");
    temp.append("-log:      \t");
    temp.append(getExtLogPath());
    temp.append("\n");
    temp.append("-no_log:   \t");
    temp.append(boolToString(getNoLog()));
    temp.append("\n");
    temp.append("-raw:      \t");
    temp.append(getRawFilePath());
    temp.append("\n");
    temp.append("-quiet:    \t");
    temp.append(boolToString(getQuiet()));
    temp.append("\n");

    temp.append("\n");
    return temp;
}
