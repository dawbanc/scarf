//----------------------------------------------------------------
// Project:                scarf
// Author:                 Dawson X Bancroft
// Date (yy/mm/dd):        24/01/03
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>

class ScarfLogger{

    enum log_level {
        LOW,
        MEDIUM,
        HIGH,
        DEBUG
    };

    enum log_level level;
    bool enable_internal_log;
    bool enable_external_log;
    const char* internal_log_path;
    const char* external_log_path;

    public:
        ScarfLogger();
        void setLogLevel(const char* level_in);
        const char* getLogLevel(void);
        void enableExtLog(void);
        void enableIntLog(void);
        void setExtLogPath(const char* file_path);
        void setIntLogPath(const char* file_path);
        void beginLog(void);
};

ScarfLogger::ScarfLogger(){
    level = MEDIUM;                 // set default log level
    internal_log_path = "null";     // do not log internal log by default
    external_log_path = "scarf_transcript"; // default external log is scarf_transcript
}

void ScarfLogger::setLogLevel(const char* level_in){
    if ( strcmp(level_in,"LOW") == 0) {
        level = LOW;
    } else if (strcmp(level_in,"MEDIUM")) {
        level = MEDIUM;
    } else if (strcmp(level_in,"HIGH")) {
        level = HIGH;
    } else if (strcmp(level_in,"DEBUG")){
        level = DEBUG;
    } else {
        std::cout << "scarf-5    \tInternal error: log level incorrectly set." << std::endl;
        exit(5);
    }
}

const char* ScarfLogger::getLogLevel(void) {
    const char* level_out;
    if (level == LOW) {
        level_out = "LOW";
    } else if (level == MEDIUM) {
        level_out = "MEDIUM";
    } else if (level == HIGH) {
        level_out = "HIGH";
    } else {
        level_out = "DEBUG";
    }
    return level_out;
}

void ScarfLogger::enableExtLog(void){
    enable_external_log = true;
}

void ScarfLogger::enableIntLog(void){
    enable_internal_log = true;
}

void ScarfLogger::setExtLogPath(const char* file_path){
    external_log_path = file_path;
}

void ScarfLogger::setIntLogPath(const char* file_path){
    internal_log_path = file_path;
}

void ScarfLogger::beginLog(void){

}


