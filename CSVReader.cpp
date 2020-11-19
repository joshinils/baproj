#include "CSVReader.h"
#include <fstream>
#include <iostream>

const int CSVReader::max_row_read = 1000000000;

CSVReader::CSVReader(std::string filename)
    : _fileName(filename)
{
    std::ifstream file(filename);
    if(!file) return;

    std::string header;
    getline(file, header);
    this->_header = Row(header);

    _fieldPrintWidths = std::vector<size_t>(this->_header._fields.size(), 0);
    for(size_t i = 0; i < _header._fields.size(); i++)
    { _fieldPrintWidths[i] = std::max(_fieldPrintWidths[i], _header._fields[i].size()); }

    auto a = std::min(max_row_read, 10000);
    this->_rows.reserve(a);

    int rows_read = 0;
    for(std::string line; getline(file, line);)
    {
        if(rows_read++ > max_row_read) break;

        const auto& newRow = this->_rows.emplace_back(Row(line));
        for(size_t i = 0; i < newRow._fields.size(); i++)
        { _fieldPrintWidths[i] = std::max(_fieldPrintWidths[i], newRow._fields[i].size()); }
    }
}

CSVReader::~CSVReader() { }


CSVReader::Row::Row(const std::string& row)
//    : _line(row)
{
    // https://stackoverflow.com/a/30338543/10314791
    enum class CSVState
    {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };

    _fields.reserve(10);

    CSVState state = CSVState::UnquotedField;
    size_t i       = 0; // index of the current field
    for(char const& c : row)
    {
        static const std::string emptyString("");
        switch(state)
        {
        case CSVState::UnquotedField:
            switch(c)
            {
            case ',': // end of field
                _fields.emplace_back(emptyString);
                i++;
                break;
            case '"': state = CSVState::QuotedField; break;
            case '\r': break; // get rid of all '\r'
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
                _fields.emplace_back(emptyString);
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

void CSVReader::printCSV() const
{
    return;
    int limit_out = 0;
    int max_out   = 12;

    std::cout << this->getFilename() << " \tcontains " << this->rowCount() << " rows:\n";

    for(size_t i = 0; i < this->getHeader().size(); i++)
    {
        if(i + 1 < this->getHeader().size())
            std::cout << std::left << std::setw(this->getPrintWidth(i) + 8)
                      << "\u201C" + this->getHeader()[i] + "\u201D" + ", ";
        else
            std::cout << std::left << std::setw(this->getPrintWidth(i) + 6)
                      << "\u201C" + this->getHeader()[i] + "\u201D";
    }
    std::cout << "\n";

    for(auto row : *this)
    {
        if(limit_out++ > max_out) break;
        for(size_t i = 0; i < row.size(); i++)
        {
            if(i + 1 < row.size())
                std::cout << std::left << std::setw(this->getPrintWidth(i) + 8) << "\u201C" + row[i] + "\u201D" + ", ";
            else
                std::cout << std::left << std::setw(this->getPrintWidth(i) + 6) << "\u201C" + row[i] + "\u201D";
        }
        std::cout << "\n";
    }
    std::cout << '\n';
}
