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
        Row(std::string line)
            : _line(line)
        { }

        ~Row() = default;

        std::string getLine() { return _line; }

    private:
        std::string _line;
    };

    Row _header;
    std::vector<Row> _rows;
};
