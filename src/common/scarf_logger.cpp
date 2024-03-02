//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/03
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "scarf_logger.h"

class ScarfLogger{

    std::string program_name;
    bool enable_internal_log;
    bool enable_external_log;
    bool enable_terminal_log;
    std::string internal_log_path;

    std::ofstream int_log;
    std::ofstream ext_log;


    private:
        // methods to print to various output streams
        void printLineToTerminal(std::string line);
        void printLineToInternalLog(std::string line);
        void printLineToExternalLog(std::string line);


    public:
        std::string external_log_path;

        ScarfLogger(void);
        ScarfLogger(std::string prog);
        void setEnableIntLog(bool input_internal);
        void setEnableExtLog(bool input_external);
        void setEnableTerLog(bool input_terminal);
        void setIntLogPath(std::string file_path);
        void setExtLogPath(std::string file_path);
        // opens the deisred streams
        void openLog(void);
        // closes the desired streams
        void closeLog(void);
        // prints a line to all streams
        void printLineToAll(std::string line);
        // prints the program information
        void printProgramVersion(void);
        // prints the program version but shorter
        void printProgramVersionShort(void);
        // print help info message
        void printHelp(void);
        // prints a warning, error, or fatal message
        void printError(char severity, int error_number, std::string description, bool terminal, bool internal, bool external);
        // prints a general message
        void printMessage(std::string description, bool terminal, bool internal, bool external);
};

ScarfLogger::ScarfLogger(void){
    enable_internal_log = false;    // default to off internal log
    enable_external_log = false;    // default to off external log
    enable_terminal_log = false;     // default to on terminal
    internal_log_path = "null";     // wait to log until paths are set
    external_log_path = "null";     // wait to log until paths are set
    program_name = "null";            // get program information (scarf or scc)
}

ScarfLogger::ScarfLogger(std::string prog){
    enable_internal_log = true;    // default to off internal log
    enable_external_log = false;    // default to off external log
    enable_terminal_log = true;     // default to on terminal
    internal_log_path = "null";     // wait to log until paths are set
    external_log_path = "null";     // wait to log until paths are set
    program_name = prog;            // get program information (scarf or scc)
}

void ScarfLogger::setEnableIntLog(bool input_internal){
    enable_internal_log = input_internal;
}

void ScarfLogger::setEnableExtLog(bool input_external){
    enable_external_log = input_external;
}

void ScarfLogger::setEnableTerLog(bool input_terminal){
    enable_terminal_log = input_terminal;
}

void ScarfLogger::setIntLogPath(std::string file_path){
    internal_log_path = file_path;
}

void ScarfLogger::setExtLogPath(std::string file_path){
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
    if (enable_terminal_log) {
        printLineToTerminal(line);
    }
    if (enable_internal_log) {
        printLineToInternalLog(line);
    }
    if (enable_external_log) {
        printLineToExternalLog(line);
    }
}

void ScarfLogger::printProgramVersion(void){
    // get time into a buffer
    time_t now = time(0);
    struct tm tstruct;
    char time_buffer[20];
    tstruct = *localtime(&now);
    strftime(time_buffer, sizeof(time_buffer), "%Y_%m_%d %H%M%S", &tstruct);
    // print logo and info
    printLineToAll("-----------------------------------------------------");
    printLineToAll("⢠⣶⣶⣶⣶⣆⠀  - " + program_name + " " + std::string(VERSION_SHORT));
    printLineToAll("⢸⣿⡛⠛⣻⣿⠀  - version: " + std::string(VERSION_LONG));
    printLineToAll("⠘⢿⣿⣿⣟⡏⠀  --------------------------------------------");
    printLineToAll(" ⢠⣿⣿⣾⣿⣆⠀ - Start time: " + std::string(time_buffer));
    printLineToAll("⠀⣾⣿⠏⠈⣿⣻⡀ --------------------------------------------");
    printLineToAll("⢸⣿⡿⠀⠀⠞⠟⠃ -");
    printLineToAll("⢸⣿⣷⠀⠀⠀⠀⠀ -");
    printLineToAll("⠓⠟⠹⠀⠀⠀⠀⠀ -");
    printLineToAll("-----------------------------------------------------");
    printLineToAll("");
}

void ScarfLogger::printProgramVersionShort(void) {
    printLineToTerminal(program_name + " " + std::string(VERSION_SHORT));
    printLineToTerminal(std::string(VERSION_LONG));
}

void ScarfLogger::printHelp(void) {
    if (program_name == "scarf") {
        // if program is scarf print scarf help
        printLineToAll("-----------------------------------------------------");
        printLineToAll("Scarf Help Message");
        printLineToAll("-----------------------------------------------------");

        printLineToAll("Example usage: scarf [options] <-raw path/to/image.raw>");
        printLineToAll("");

        printLineToAll("\t-conf <path/to/conf.yaml>:");
        printLineToAll("\t\tSpecifies the path to the configuration yaml file.");
        printLineToAll("");

        printLineToAll("\t-csv_file <csv_file_output>:");
        printLineToAll("\t\tSpecify the output CSV file.");
        printLineToAll("");

        printLineToAll("\t-debug:");
        printLineToAll("\t\tPrints out additional information to debug the program.");
        printLineToAll("");

        printLineToAll("\t--h || --help:");
        printLineToAll("\t\tPrints out the help information.");
        printLineToAll("");

        printLineToAll("\t-log <path>:");
        printLineToAll("\t\tSpecifies the log path rather than $PWD/scarf_log");
        printLineToAll("");

        printLineToAll("\t-no_log:");
        printLineToAll("\t\tWill not print out the transcript");
        printLineToAll("");

        printLineToAll("\t-raw <path/to/image.raw>:");
        printLineToAll("\t\tSpecifies the path to the raw image to pull data from");
        printLineToAll("");

        printLineToAll("\t-quiet:");
        printLineToAll("\t\tSuppresses terminal output");
        printLineToAll("");

        printLineToAll("\t-version || --version:");
        printLineToAll("\t\tPrint out version info and exit.");
        printLineToAll("");

    } else if (program_name == "scc") {
        // if program is scc print scc help

    } else {
        //fatal error
        printError('F', 19, "Internal error has occured. " + program_name + " is not a valid program.", true, true, true);
    }
    closeLog();
    exit(1);
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
