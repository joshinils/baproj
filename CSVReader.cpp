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


CSVReader::Row::Row(std::string row)
    : _line(row)
{
    enum class CSVState
    {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };

    // https://stackoverflow.com/a/30338543/10314791
    CSVState state = CSVState::UnquotedField;
    size_t i       = 0; // index of the current field
    for(char c : row)
    {
        switch(state)
        {
        case CSVState::UnquotedField:
            switch(c)
            {
            case ',': // end of field
                _fields.push_back("");
                i++;
                break;
            case '"': state = CSVState::QuotedField; break;
            default: _fields[i].push_back(c); break;
            }
            break;
        case CSVState::QuotedField:
            switch(c)
            {
            case '"': state = CSVState::QuotedQuote; break;
            default: _fields[i].push_back(c); break;
            }
            break;
        case CSVState::QuotedQuote:
            switch(c)
            {
            case ',': // , after closing quote
                _fields.push_back("");
                i++;
                state = CSVState::UnquotedField;
                break;
            case '"': // "" -> "
                _fields[i].push_back('"');
                state = CSVState::QuotedField;
                break;
            default: // end of quote
                state = CSVState::UnquotedField;
                break;
            }
            break;
        }
    }

    // for(auto l : _fields)
    // {
    //     std::cout << l << '\n';
    // }
}
