#pragma once

#include <string>
#include <vector>

class CSVReader
{
public:
    CSVReader(std::string filename);
    ~CSVReader();

    auto begin() { return _rows.begin(); }
    auto end() { return _rows.end(); }

private:
    class Row
    {
    public:
        Row() = default;
        Row(std::string line);

        ~Row() = default;

        std::string getLine() { return _line; }
        auto begin() { return _fields.begin(); }
        auto end() { return _fields.end(); }

    private:
        std::string _line;
        std::vector<std::string> _fields{ "" };
    };

    Row _header;
    std::vector<Row> _rows;
};
