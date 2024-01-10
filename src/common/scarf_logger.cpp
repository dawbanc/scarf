//----------------------------------------------------------------
// Project:                scarf
// Author:                 Dawson X Bancroft
// Date (yy/mm/dd):        24/01/03
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>

#include "version.h"

class ScarfLogger{

    enum log_level {
        LOW,
        MEDIUM,
        HIGH,
        DEBUG
    };

    enum log_level level;
    std::string program_name;
    bool enable_internal_log;
    bool enable_external_log;
    const char* internal_log_path;
    const char* external_log_path;
    std::ofstream int_log;
    std::ofstream ext_log;


    public:
        ScarfLogger(std::string prog);
        void setLogLevel(const char* level_in);
        const char* getLogLevel(void);
        void enableIntLog(void);
        void enableExtLog(void);
        void setIntLogPath(const char* file_path);
        void setExtLogPath(const char* file_path);
        void openLog(void);
        void closeLog(void);
        void printLineToTerminal(std::string line);
        void printLineToInternalLog(std::string line);
        void printLineToExternalLog(std::string line);
        void printLineToAll(std::string line);
        void printProgramVersion(void);
};

ScarfLogger::ScarfLogger(std::string prog){
    level = MEDIUM;                 // set default log level
    internal_log_path = "null";     // wait to log until paths are set
    external_log_path = "null";     // wait to log until paths are set
    program_name = prog;                 // get program information (scarf or scc)
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
        std::cout << "scarf-5    FATAL:\tInternal error: log level incorrectly set." << std::endl;
        std::cout << "Attempted to put in " << level_in << std::endl;
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

void ScarfLogger::enableIntLog(void){
    enable_internal_log = true;
}

void ScarfLogger::enableExtLog(void){
    enable_external_log = true;
}

void ScarfLogger::setIntLogPath(const char* file_path){
    internal_log_path = file_path;
}

void ScarfLogger::setExtLogPath(const char* file_path){
    external_log_path = file_path;
}

void ScarfLogger::openLog(void){
    if (enable_internal_log) {
        int_log.open(internal_log_path);
    }
    if (enable_external_log) {
        ext_log.open(external_log_path);
    }
}

void ScarfLogger::closeLog(void){
    if (enable_internal_log) {
        int_log.close();
    }
    if (enable_external_log) {
        ext_log.close();
    }
}

void ScarfLogger::printLineToTerminal(std::string line){
    std::cout << line << std::endl;
}

void ScarfLogger::printLineToInternalLog(std::string line){
    int_log << line << std::endl;
}

void ScarfLogger::printLineToExternalLog(std::string line){
    ext_log << line << std::endl;
}

void ScarfLogger::printLineToAll(std::string line){
    printLineToTerminal(line);
    printLineToInternalLog(line);
    printLineToExternalLog(line);
}

void ScarfLogger::printProgramVersion(void){
    // print logo and info
    printLineToAll("--------------------------------------------------");
    printLineToAll("⢠⣶⣶⣶⣶⣆⠀  - " + program_name + " " + std::string(VERSION_SHORT));
    printLineToAll("⢸⣿⡛⠛⣻⣿⠀  - version: " + std::string(VERSION_LONG));
    printLineToAll("⠘⢿⣿⣿⣟⡏⠀  -");
    printLineToAll(" ⢠⣿⣿⣾⣿⣆⠀ -");
    printLineToAll("⠀⣾⣿⠏⠈⣿⣻⡀ -");
    printLineToAll("⢸⣿⡿⠀⠀⠞⠟⠃ -");
    printLineToAll("⢸⣿⣷⠀⠀⠀⠀⠀ -");
    printLineToAll("⠓⠟⠹⠀⠀⠀⠀⠀ -");
    printLineToAll("--------------------------------------------------");
    printLineToAll("");
}
