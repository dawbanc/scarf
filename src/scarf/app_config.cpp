#include <iostream>

class AppConfig {
	public:
		bool debug = false;
        std::string raw_file_location = "null";
    void printVersionString() {
        std::cout << " version: v0.0.0_231223_2232" << std::endl;
    };
    void printInfo() {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << " scarf v0.0.0" << std::endl;
        printVersionString();
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << std::endl;
    };
    void printHelp() {
        std::cout << "--help option used. You may not run the program when using this option." << std::endl;
        std::cout << "Here is a quick overview of options. Please read the docs for more detailed descriptions." << std::endl;
        std::cout << "General usages: " << std::endl;
        std::cout << "\tscarf -raw /home/jreese/Downloads/sdCardPull.raw" << std::endl;
        // TODO: Add more usages
        std::cout << std::endl;
        std::cout << "scarf will now exit." << std::endl;
    };
    void printAppConfig() {
        std::cout << "App Configuration:" << std::endl;
        std::cout << "\tdebug:        \t\t" << debug << std::endl;
        std::cout << "\traw file path:\t\t" << raw_file_location << std::endl;

        std::cout << std::endl;
    };
};
