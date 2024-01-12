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

    std::string program_name;
    bool enable_internal_log;
    bool enable_external_log;
    const char* internal_log_path;
    const char* external_log_path;
    std::ofstream int_log;
    std::ofstream ext_log;


    private:
        void enableIntLog(void);
        void enableExtLog(void);
        void printLineToTerminal(std::string line);
        void printLineToInternalLog(std::string line);
        void printLineToExternalLog(std::string line);


    public:
        ScarfLogger(std::string prog);
        void setIntLogPath(const char* file_path);
        void setExtLogPath(const char* file_path);
        void openLog(void);
        void closeLog(void);
        void printLineToAll(std::string line);
        void printProgramVersion(void);
        void printError(char severity, int error_number, std::string description, bool terminal, bool internal, bool external);
        void printMessage(std::string description, bool terminal, bool internal, bool external);
};

ScarfLogger::ScarfLogger(std::string prog){
    internal_log_path = "null";     // wait to log until paths are set
    external_log_path = "null";     // wait to log until paths are set
    program_name = prog;            // get program information (scarf or scc)
}

void ScarfLogger::enableIntLog(void){
    enable_internal_log = true;
}

void ScarfLogger::enableExtLog(void){
    enable_external_log = true;
}

void ScarfLogger::setIntLogPath(const char* file_path){
    internal_log_path = file_path;
    enableIntLog();
}

void ScarfLogger::setExtLogPath(const char* file_path){
    external_log_path = file_path;
    enableExtLog();
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
    // get time into a buffer
    time_t now = time(0);
    struct tm tstruct;
    char time_buffer[20];
    tstruct = *localtime(&now);
    strftime(time_buffer, sizeof(time_buffer), "%Y_%m_%d %H%M%S", &tstruct);
    // print logo and info
    printLineToAll("--------------------------------------------------");
    printLineToAll("⢠⣶⣶⣶⣶⣆⠀  - " + program_name + " " + std::string(VERSION_SHORT));
    printLineToAll("⢸⣿⡛⠛⣻⣿⠀  - version: " + std::string(VERSION_LONG));
    printLineToAll("⠘⢿⣿⣿⣟⡏⠀  -----------------------------------------");
    printLineToAll(" ⢠⣿⣿⣾⣿⣆⠀ - Start time: " + std::string(time_buffer));
    printLineToAll("⠀⣾⣿⠏⠈⣿⣻⡀ -----------------------------------------");
    printLineToAll("⢸⣿⡿⠀⠀⠞⠟⠃ -");
    printLineToAll("⢸⣿⣷⠀⠀⠀⠀⠀ -");
    printLineToAll("⠓⠟⠹⠀⠀⠀⠀⠀ -");
    printLineToAll("--------------------------------------------------");
    printLineToAll("");
}

void ScarfLogger::printError(char severity, int error_number, std::string description, bool terminal, bool internal, bool external){
    //severity char: W for Warning, E for Error, and F for Fatal
    std::string message_out;

    // get correct spaces in error message for error number
    std::string error_number_string;
    if (error_number < 10) {
        error_number_string = std::to_string(error_number) + "    ";
    } else if (error_number < 100) {
        error_number_string = std::to_string(error_number) + "   ";
    } else if (error_number < 1000) {
        error_number_string = std::to_string(error_number) + "  ";
    } else if (error_number < 10000) {
        error_number_string = std::to_string(error_number) + " ";
    } else {
        error_number_string = std::to_string(error_number);
    }

    // get the warning, error, or fatal string
    std::string severity_string;
    if (severity == 'W') {
        severity_string = "WARNING";
    } else if (severity == 'E') {
        severity_string = "ERROR";
    } else {                                        // as if it isn't a W or an E assume it is fatal
        severity_string = "FATAL";
    }

    // put everything together
    message_out = program_name + "-" + error_number_string + "\t" + severity_string + ": " + description;

    // print it out where it needs to
    if (terminal) {
        printLineToTerminal(message_out);
    }
    if (internal && enable_internal_log) {
        printLineToInternalLog(message_out);
    }
    if (external && enable_external_log) {
        printLineToExternalLog(message_out);
    }

    // if a Fatal error occurs, stop the program
    if (severity == 'F') {
        closeLog();
        exit(1);
    }
}

void ScarfLogger::printMessage(std::string description, bool terminal, bool internal, bool external){
    std::string message_out;
    message_out = program_name + "-Gen  \tMessage: " + description;
    if (terminal) {
        printLineToTerminal(message_out);
    }
    if (internal && enable_internal_log) {
        printLineToInternalLog(message_out);
    }
    if (external && enable_external_log) {
        printLineToExternalLog(message_out);
    }
}
