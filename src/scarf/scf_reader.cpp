//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/01/23
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include <filesystem>
#include <iostream>

class ScfReader{

    private:
        bool image_data = false;
        bool data_points_in_config = false;
        int num_data_points = 0;
        int num_config_blocks = 0;
        int num_data_blocks = 0;
        int num_bytes_per_data_block = 0;

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
    if (config_file.is_open()) {
        while(config_file) {
            std::getline(config_file, scf_line);
            // remove whitespace ahead of actual info
            bool has_preceeding_whitespace = true;
            while (has_preceeding_whitespace){
                if (scf_line[0] == ' '){
                    scf_line.erase(0, 1);
                } else {
                    has_preceeding_whitespace = false;
                }
                if (scf_line.size() == 0 ) {
                    has_preceeding_whitespace = false;
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
            logger->printMessage(    "ScfReader line read    : " + scf_line, false, true, false);
            if (!comment.empty()) {
                logger->printMessage("ScfReader comment read : " + comment, false, true, false);
            }

        }
    }


}
