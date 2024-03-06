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

public:
    void setRawFilePath(std::string input_raw_file_path);
    std::string getRawFilePath(void);
    void openRawFile(void);
    void closeFile(void);
};

void RawReader::setRawFilePath(std::string input_raw_file_path) {
    raw_file_path = input_raw_file_path;
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
