//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/23
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "scarf_reader.h"

class ScfReader{

    private:
        bool image_data = false;
        bool data_points_in_config = false;
        int num_data_points = 0;
        int num_config_blocks = 0;
        int num_data_blocks = 0;
        int num_bytes_per_data_block = 0;

        std::map<std::string, std::string> configuration_value_m;


        std::string scf_file_path = "null";
        int line_cnt = 0;

        // set of keys to get from the configuration file
        std::vector<std::string> scf_dedicated_keys = { "IMAGE_DATA",
                                                        "DATA_POINTS_IN_CONFIG",
                                                        "NUMBER_DATA_POINTS",
                                                        "NUMBER_CONFIG_BLOCKS",
                                                        "NUMBER_DATA_BLOCKS",
                                                        "NUMBER_BYTES_PER_DATA_BLOCKS",
                                                        "CONFIG",
                                                        "DATA",
                                                        "CSV_COL_LABELS",
                                                        "CSV_COL_MATH"};



        bool to_bool(std::string s);
        int to_integer(std::string s);

        bool parseConfigValues(std::string input_value);
    public:
        ScarfLogger* logger;
        void readScfFile(std::string scf_file_path);

};

bool ScfReader::to_bool(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s == "true"){
        return true;
    } else if (s == "false") {
        return false;
    } else {
        logger->printError('E', 6, scf_file_path + "(" + std::to_string(line_cnt) + "): A configuration variable is a wrong type. A default value will be used.", true, true, true);
        return false;
    }
}

int ScfReader::to_integer(std::string s) {
    int num = 0;
    try {
        num = std::stoi(s);
    } catch (const std::invalid_argument& e) {
        logger->printError('E', 6, scf_file_path + "(" + std::to_string(line_cnt) + "): A configuration variable is a wrong type. A default value will be used.", true, true, true);
        num = 0;
    }
    return num;
}

bool ScfReader::parseConfigValues(std::string input_string){
    // lets find and remove the {}
    if (input_string.find('{') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error: CONFIG: missing \'{\'", true, true, true);
    }
    if (input_string.find('}') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error: CONFIG: missing \'}\'", true, true, true);
    }
    input_string.erase(0, 1); // remove {
    input_string.erase(input_string.size()-1); // remove }

    // split the string into values
    std::stringstream ss(input_string);
    std::string value;
    while (std::getline(ss, value, ',')) {
        // create a string key IE CONFIG000_BYTE000

        // add to map
    }

    return true;
}

void ScfReader::readScfFile(std::string scf_file_path_in){
    // copy to a local variable
    scf_file_path = scf_file_path_in;

    // check to see if file exists
    logger->printMessage("ScfReader starting...\n", false, true, false);
    if (!std::filesystem::exists(scf_file_path)){
        logger->printError('F', 2, "The file path specified by \"-conf\" does not exist:" + scf_file_path, true, true, true);
    }


    // read in the lines
    std::ifstream config_file;
    config_file.open(scf_file_path);
    std::string scf_line;
    if (config_file.is_open()) {
        while(config_file) {
            std::getline(config_file, scf_line);
            line_cnt++;
            // remove whitespace ahead and behind of actual info
            bool has_preceeding_whitespace = true;
            while (has_preceeding_whitespace){
                if (scf_line.empty()) {
                    has_preceeding_whitespace = false;
                } else {
                    if (scf_line[0] == ' '){
                        scf_line.erase(0, 1);
                    } else {
                        has_preceeding_whitespace = false;
                    }
                }
            }
            bool has_foregoing_whitespace = true;
            while (has_foregoing_whitespace) {
                if (scf_line.empty()) {
                    has_foregoing_whitespace = false;
                } else {
                    if (scf_line.back() == ' ') {
                        scf_line.erase(scf_line.size() - 1);
                    } else {
                        has_foregoing_whitespace = false;
                    }
                }
            }

            // detect if the line is empty
            if (scf_line.empty()) {
                continue;
            }

            // comments detection
            std::string comment;
            if (scf_line.find('#') != std::string::npos) {
                size_t hash_tag_position = scf_line.find('#');
                std::string temp_line = scf_line.substr(0, hash_tag_position);
                comment = scf_line.substr(hash_tag_position);
                scf_line.assign(temp_line);
            }

            if (!comment.empty()) {
                logger->printMessage("ScfReader comment read : " + comment, false, true, false);
            }
            if (scf_line.empty()) {
                continue;
            }
            logger->printMessage(    "ScfReader line read    : " + scf_line, false, true, false);

            // need to see if the key is something we recognize
            std::string key, value;
            if (scf_line.find('=') == std::string::npos) {
                logger->printError('E', 4, scf_file_path + "(" + std::to_string(line_cnt) + "): Syntax error: No equal sign detected.", true, true, true);
                continue;
            } else {
                if (scf_line.find(';') == std::string::npos) {
                    logger->printError('E', 4, scf_file_path + "(" + std::to_string(line_cnt) + "): Syntax error: No semicolon sign detected.", true, true, true);
                    continue;
                }
                std::string temp_line;
                size_t equal_position = scf_line.find('=');
                size_t semi_colon_position = scf_line.find(';');
                temp_line = scf_line.substr(0, semi_colon_position);
                key = temp_line.substr(0, equal_position);
                value = temp_line.substr(equal_position+1);
            }
            logger->printMessage("ScfReader: key parsed  : " + key, false, true, false);
            logger->printMessage("ScfReader: value parsed: " + value, false, true, false);

            // if it is a key we recognize parse it https://g.co/bard/share/4af42dfc768e
            bool recognized_key = std::any_of(scf_dedicated_keys.begin(), scf_dedicated_keys.end(),
                                        [&key](const std::string& word) {
                                            return word == key;
                                        });

            if (recognized_key) {
                if (key.compare("IMAGE_DATA") == 0){
                    image_data = to_bool(value);
                    logger->printMessage("ScfReader: img data set: " + value, false, true, false);
                } else if (key.compare("DATA_POINTS_IN_CONFIG") == 0) {
                    data_points_in_config = to_bool(value);
                    logger->printMessage("ScfReader: dp in config: " + value, false, true, false);
                } else if (key.compare("NUMBER_DATA_POINTS") == 0) {
                    num_data_points = to_integer(value);
                    logger->printMessage("ScfReader: num of db   : " + std::to_string(num_data_points), false, true, false);
                } else if (key.compare("NUMBER_CONFIG_BLOCKS") == 0) {
                    num_config_blocks = to_integer(value);
                    logger->printMessage("ScfReader: num cfg blks: " + std::to_string(num_config_blocks), false, true, false);
                } else if (key.compare("NUMBER_DATA_BLOCKS") == 0) {
                    num_data_blocks = to_integer(value);
                    logger->printMessage("ScfReader: num data blk: " + std::to_string(num_data_blocks), false, true, false);
                } else if (key.compare("NUMBER_BYTES_PER_DATA_BLOCKS") == 0) {
                    num_bytes_per_data_block = to_integer(value);
                    logger->printMessage("ScfReader: bytes / dblk: " + std::to_string(num_bytes_per_data_block), false, true, false);
                } else if (key.compare("CONFIG") == 0) {
                    bool config_parse_status = false;
                    // TODO: add config block label parsing
                    logger->printMessage("ScfReader: cfg blk pars: " + std::to_string(config_parse_status), false, true, false); // TODO: add boolean return value from config parsing and print it
                } else if (key.compare("DATA") == 0) {
                    bool data_parse_status = false;
                    // TODO: add data block label parsing
                    logger->printMessage("ScfReader: data blk par: " + std::to_string(data_parse_status), false, true, false); // TODO: add boolean return value from data parsing and print it
                } else if (key.compare("CSV_COL_LABELS") == 0) {
                    bool csv_col_labels_parse_status = false;
                    // TODO: add csv label parsing
                    logger->printMessage("ScfReader: csv head par: " + std::to_string(csv_col_labels_parse_status), false, true, false); // TODO: add boolean return value from csv label parsing and print it
                } else if (key.compare("CSV_COL_MATH") == 0) {
                    bool csv_col_math_parse_status = false;
                    // TODO: add csv col math parsing
                    logger->printMessage("ScfReader: csv col pars: " + std::to_string(csv_col_math_parse_status), false, true, false); // TODO: add boolean return value from csv column math parsing and print it
                } else {
                    logger->printError('F', 7, "ScfReader: Unable to parse:" + key + "\n                with value:" + value, true, true, true);
                }

            } else {
            // else put it in a map for constants (and print a message saying it is not a default option)

            }

            // some error checking (IE number of data blocks is 0 or number of config blocks is 0 and CONFIG is defined)
        }
    }


}
