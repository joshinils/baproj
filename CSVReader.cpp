#include "CSVReader.h"
#include <fstream>
#include <iostream>

CSVReader::CSVReader(std::string filename)
{
    std::ifstream file(filename);
    if(!file) return;

    std::string header;
    getline(file, header);
    this->_header = Row(header);

    for(std::string line; getline(file, line);) { this->_rows.push_back(Row(line)); }
}

CSVReader::~CSVReader() { }
