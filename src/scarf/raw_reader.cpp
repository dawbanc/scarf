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
    void closeRawFile(void);

    //TODO: Change from void
    void readBlock(unsigned long int block_number);
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
    if(!raw_file) {
        logger->printError('F', 20, "RawReader: Error opening the raw file path.", true, true, true);
    }
}

void RawReader::closeRawFile(void) {
    raw_file.close();
}

void RawReader::readBlock(unsigned long int block_number) {
    // move pointer to the the desired block
    raw_file.seekg(raw_file.beg);
    raw_file.seekg(block_number*512);
    unsigned char block_buffer[512];
    raw_file.read( (char*)( &block_buffer[0]), 512);

    // convert to a more readable format
    char buffer [1024];
    buffer[1023] = 0;
    for (int i=0; i<512; i++) {
        sprintf(&buffer[2*i], "%02x", block_buffer[i]);
    }

    logger->printMessage("RawReader: Block number: " + std::to_string(block_number) + "\n\t" + buffer, false, true, false);

}
