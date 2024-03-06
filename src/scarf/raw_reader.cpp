//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/03/05
// Notes:
// For changes view git history
//----------------------------------------------------------------

#include "raw_reader.h"

class RawReader{

private:
    std::string raw_file_path;
    std::ifstream raw_file;
    ScarfLogger* logger;

public:
    RawReader(std::string raw_file_path_in, ScarfLogger* logger_in);
    void setRawFilePath(std::string raw_file_path_in);
    std::string getRawFilePath(void);
    void openRawFile(void);
    void closeFile(void);
};

RawReader::RawReader(std::string raw_file_path_in, ScarfLogger* logger_in) {
    raw_file_path = raw_file_path_in;
    logger = logger_in;
}

void RawReader::setRawFilePath(std::string raw_file_path_in) {
    raw_file_path = raw_file_path_in;
}

std::string RawReader::getRawFilePath(void) {
    return raw_file_path;
}

void RawReader::openRawFile(void) {
    raw_file.open(raw_file_path, std::ifstream::binary);

    // print error if file cannot be opened

}

void RawReader::closeFile(void) {
    raw_file.close();
}
