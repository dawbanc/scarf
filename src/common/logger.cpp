#include <iostream>
#include <cstring>

class Logger{

    enum log_level {
        LOW,
        MEDIUM,
        HIGH,
        DEBUG
    };

    private:
        enum log_level level;
    public:
        void set_log_level(const char* level_in){
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



};
