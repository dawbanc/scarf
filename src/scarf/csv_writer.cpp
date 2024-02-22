//----------------------------------------------------------------
// Project:                scarf
// Author:                 dawbanc
// Date (yy/mm/dd):        24/02/20
// Notes:
// For changes view git history
//----------------------------------------------------------------
#include "csv_writer.h"

class CsvWriter{

private:
    std::string csv_file_path;
    int num_col;

public:
    CsvWriter(std::string csv_file_path_in, int num_col_in);
};

CsvWriter::CsvWriter(std::string csv_file_path_in, int num_col_in) {
    csv_file_path = csv_file_path_in;
    num_col = num_col_in;
}


