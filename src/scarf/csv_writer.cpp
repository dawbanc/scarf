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
    long unsigned int num_col;
    ScarfLogger* logger;
    std::ofstream csv_file;

public:
    CsvWriter(std::string csv_file_path_in, int num_col_in, ScarfLogger* logger_in);
    bool openCsvFile(void);
    bool closeCsvFile(void);
    bool writeColumnHeaders(std::map<std::string, std::string> headers);
    bool writeData(std::map<std::string, std::string> data_map);
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

    if (headers.size() != num_col) {
        logger->printError('E', 18, "CsvWriter header map size and number of columns do not match.", true, true, true);
    }

    for (long unsigned int i=0; i < num_col; i++) {
        std::string key = "COL_HEADER_" + std::to_string(i);
        csv_file << headers[key] << ",";
    }

    csv_file << std::endl;

    logger->printMessage("CsvWriter: Headers written to " + csv_file_path, false, true, false);

    return true;
}

bool CsvWriter::writeData(std::map<std::string, std::string> data_map) {
    if (data_map.size() != num_col) {
        logger->printError('E', 18, "CsvWriter data map size and number of columns do not match.", true, true, true);
    }

    for (long unsigned int i=0; i < num_col; i++) {
        std::string key = "COL" + std::to_string(i);
        csv_file << data_map[key] << ",";
    }

    csv_file << std::endl;

    logger->printMessage("CsvWriter: Headers written to " + csv_file_path, false, true, false);

    return true;
}
