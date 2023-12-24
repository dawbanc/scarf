#include <iostream>
#include <cstring>

class AppConfig {
	public:
		bool debug;
};

void AppConfig::printVersionString() {
                        std::cout << " scarf v0,0,0_231223_2232" << std::endl;
};

void AppConfig::printHelp() {
                        std::cout << std::endl;
                        std::cout << "--------------------------------------------------" << std::endl;
                        std::cout << " scarf" << std::endl;
                        std::cout << std::endl;
                        this.printVersionString();
                        std::cout << std::endl;
                        std::cout << "--------------------------------------------------" << std::endl;
};
