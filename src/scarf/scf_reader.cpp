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

        std::vector<std::string> scf_dedicated_keys = { "IMAGE_DATA",
                                                        "DATA_POINTS_IN_CONFIG",
                                                        "NUMBER_DATA_POINTS",
                                                        "NUMBER_CONFIG_BLOCKS",
                                                        "NUMBER_DATA_BLOCKS",
                                                        "NUMBER_BYTES_PER_DATA_BLOCKS",
                                                        "CONFIG_BLOCK",
                                                        "DATA",
                                                        "CSV_COL_LABELS",
                                                        "CSV_COL_MATH"};

    public:
        ScarfLogger* logger;
        void readScfFile(std::string scf_file_path);

};

void ScfReader::readScfFile(std::string scf_file_path){
    // check to see if file exists
    logger->printMessage("ScfReader starting...\n", false, true, false);
    if (!std::filesystem::exists(scf_file_path)){
        logger->printError('F', 2, "The file path specified by \"-conf\" does not exist.", true, true, true);
    }

    // read in the lines
    std::ifstream config_file;
    config_file.open(scf_file_path);
    std::string scf_line;
    int line_cnt = 0;
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

            // else put it in a map for constants (and print a message saying it is not a default option)

        }
    }


}
