//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/02/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "csv_writer.h"

//template <typename K, typename V>
class CsvWriter{

private:
    std::string csv_file_path;
    int num_col;
    ScarfLogger* logger;
    std::ofstream csv_file;

public:
    CsvWriter(std::string csv_file_path_in, int num_col_in, ScarfLogger* logger_in);
    bool openCsvFile(void);
    bool closeCsvFile(void);
    bool writeColumnHeaders(std::map<std::string, std::string> headers);

};

CsvWriter::CsvWriter(std::string csv_file_path_in, int num_col_in, ScarfLogger* logger_in) {
    csv_file_path = csv_file_path_in;
    num_col = num_col_in;
    logger = logger_in;
}

bool CsvWriter::openCsvFile(void){
    if (csv_file_path.empty()) {
        logger->printError('F', 16, "CsvWriter: CSV file path is null", true, true, true);
        return false;
    }

    csv_file.open(csv_file_path);
    if(!csv_file.is_open()) {
        logger->printError('F', 17, "CsvWriter: CSV file path cannot be written to.", true, true, true);
    }

    return true;
}

bool CsvWriter::closeCsvFile(void){
    csv_file.close();
    return true;
}

bool CsvWriter::writeColumnHeaders(std::map<std::string, std::string> headers){

    for (int i=0; i < headers.size()-1; i++) {
        std::string key = "COL_HEADER_" + std::to_string(i);
        csv_file << headers[key] << ",";
    }

    csv_file << std::endl;

    return true;
}
