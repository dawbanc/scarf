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
        std::map<std::string, std::string> data_value_m;
        std::map<std::string, std::string> csv_labels_m;
        std::map<std::string, std::string> csv_math_m;

        std::map<std::string, std::string> constants_m;


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

        bool parseConfigValues(std::string input_string);
        bool parseDataValues(std::string input_string);
        bool parseCsvLabelValues(std::string input_string);
        bool parseCsvMathValues(std::string input_string);
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
    int block = 0;
    int byte  = 0;
    while (std::getline(ss, value, ',')) {
        // create a string key IE CONFIG0_BYTE0
        std::string key = "CONFIG" + std::to_string(block) + "_BYTE" + std::to_string(byte);
        // add to map
        configuration_value_m[key] = value;
        logger->printMessage("ScfReader: PARSE CONFIG: configuration_value_m[" + key + "] = " + value, false, true, false);
        // increment counters
        if (byte == 511) {
            block++;
            byte = 0;
        } else {
            byte++;
        }
    }
    return true;
}

bool ScfReader::parseDataValues(std::string input_string){
    // lets find and remove the {}
    if (input_string.find('{') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'{\'", true, true, true);
    }
    if (input_string.find('}') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'}\'", true, true, true);
    }
    input_string.erase(0, 1); // remove {
    input_string.erase(input_string.size()-1); // remove }

    // split the string into values
    std::stringstream ss(input_string);
    std::string value;
    int block = 0;
    int byte  = 0;
    while (std::getline(ss, value, ',')) {
        // create a string key IE CONFIG0_BYTE0
        std::string key = "DATA" + std::to_string(block) + "_BYTE" + std::to_string(byte);
        // add to map
        data_value_m[key] = value;
        logger->printMessage("ScfReader: PARSE DATA  :          data_value_m[" + key + "] = " + value, false, true, false);
        // increment counters
        if (byte == 511) {
            block++;
            byte = 0;
        } else {
            byte++;
        }
    }
    return true;
}

bool ScfReader::parseCsvLabelValues(std::string input_string){
    // lets find and remove the {}
    if (input_string.find('{') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'{\'", true, true, true);
    }
    if (input_string.find('}') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'}\'", true, true, true);
    }
    input_string.erase(0, 1); // remove {
    input_string.erase(input_string.size()-1); // remove }

    // split the string into values
    std::stringstream ss(input_string);
    std::string value;
    int column_number = 0;
    while (std::getline(ss, value, ',')) {
        // create a string key IE CONFIG0_BYTE0
        std::string key = "COL_HEADER_" + std::to_string(column_number);
        // add to map
        csv_labels_m[key] = value;
        logger->printMessage("ScfReader:PARSE CSVHEAD:          data_value_m[" + key + "] = " + value, false, true, false);
        // increment counters
        column_number++;
    }
    return true;
}

bool ScfReader::parseCsvMathValues(std::string input_string) {
    // lets find and remove the {}
    if (input_string.find('{') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'{\'", true, true, true);
    }
    if (input_string.find('}') == std::string::npos) {
        logger->printError('E', 8, "Configuration value has a syntax error:   DATA: missing \'}\'", true, true, true);
    }
    input_string.erase(0, 1); // remove {
    input_string.erase(input_string.size()-1); // remove }

    //parse the math even if parenthesis are involved
    std::stack<char> parenthesis_stack;
    std::string current_key;
    std::string current_value;
    int value_cnt = 0;

    for (char c : input_string) {
        if (c == '(') {
            parenthesis_stack.push(c);
        } else if (c == ')') {
            if (parenthesis_stack.empty()) {
                // THROW FATAL MISMATCHED PARETHESIS IN MATH CONFIG ITEM NUM
                logger->printError('F', 9, "ScfReader: CSV_COL_MATH mismatched parenthesis after " + std::to_string(value_cnt) + " commas.", true, true, true);
            }
            parenthesis_stack.pop();
        } else if (c == ',' && parenthesis_stack.empty()) {
            // create key
            // insert in map
            // clear current value
            current_key = "COL" + std::to_string(value_cnt);
            csv_math_m[current_key] = current_value;
            logger->printMessage("ScfReader:PARSE CSVMATH:            csv_math_m[" + current_key + "] = " + current_value, false, true, false);
            current_value.clear();
            current_key.clear();
            value_cnt++;
        } else {
            current_value += c;
        }
    }

    if (!current_value.empty()) {
        // if current_value isn't  empty then add it to the map
        current_key = "COL" + std::to_string(value_cnt);
        csv_math_m[current_key] = current_value;
        current_value.clear();
        current_key.clear();
        value_cnt++;
    }
    logger->printMessage("ScfReader:PARSE CSVMATH: sucessfully read in " + std::to_string(value_cnt) + " values", false, true, false);
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
                    config_parse_status = parseConfigValues(value);
                    logger->printMessage("ScfReader: cfg blk pars: " + std::to_string(config_parse_status), false, true, false);
                } else if (key.compare("DATA") == 0) {
                    bool data_parse_status = false;
                    data_parse_status = parseDataValues(value);
                    logger->printMessage("ScfReader: data blk par: " + std::to_string(data_parse_status), false, true, false);
                } else if (key.compare("CSV_COL_LABELS") == 0) {
                    bool csv_col_labels_parse_status = false;
                    csv_col_labels_parse_status = parseCsvLabelValues(value);
                    logger->printMessage("ScfReader: csv head par: " + std::to_string(csv_col_labels_parse_status), false, true, false);
                } else if (key.compare("CSV_COL_MATH") == 0) {
                    bool csv_col_math_parse_status = false;
                    csv_col_math_parse_status = parseCsvMathValues(value);
                    logger->printMessage("ScfReader: csv col pars: " + std::to_string(csv_col_math_parse_status), false, true, false);
                } else {
                    logger->printError('F', 7, "ScfReader: Unable to parse:" + key + "\n                with value:" + value, true, true, true);
                }
            } else {
                // else put it in a map for constants (and print a message saying it is not a default option)
                logger->printError('W', 10, "ScfReader: Unrecognized option :" + key + "\n                with value:" + value + \
                                            "                                Adding to the constants map.", true, true, true);
                constants_m[key] = value;
            }
        }
    }
    // some error checking (IE number of data blocks is 0 or number of config blocks is 0 and CONFIG is defined)
    if (num_data_points == 0) {
        logger->printError('F', 11, "ScfReader: num_data_points is 0 : Either NUMBER_DATA_POINTS is undefined in the config file or it is set to 0. Please define this as a number greater than 0.", true, true, true);
    }
    if (csv_labels_m.size() == 0) {
        logger->printError('F', 12, "ScfReader: CSV_COL_LABELS is undefined : Please define CSV_COL_LABELS in the configuration file.", true, true, true);
    }
    if (csv_math_m.size() == 0) {
        logger->printError('F', 14, "ScfReader: CSV_COL_MATH is undefined : Please define CSV_COL_MATH in the configuration file.", true, true, true);
    }
    if ((num_config_blocks == 0) && (configuration_value_m.size() != 0)) {
        logger->printError('E', 15, "ScfReader: NUMBER_CONFIG_BLOCKS is set to 0, but CONFIG has values.", true, true, true);
    }
    logger->printMessage("ScfReader: config file parsed: " + scf_file_path_in, true, true, true);
}
