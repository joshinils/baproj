#pragma once

#include <string>
#include <vector>

class CSVReader
{
private:
    class Row;

public:
    CSVReader(std::string filename);
    ~CSVReader();

    auto begin() const { return _rows.begin(); }
    auto end() const { return _rows.end(); }

    const Row& getHeader() const { return _header; }
    size_t rowCount() const { return _rows.size(); }
    std::string getFilename() const { return _fileName; }

    size_t getPrintWidth(size_t fieldId) const { return _fieldPrintWidths.at(fieldId); }

private:
    class Row
    {
        friend CSVReader;

    public:
        Row() = default;
        Row(std::string line);

        ~Row() = default;

        std::string getLine() { return _line; }
        auto begin() const { return _fields.begin(); }
        auto end() const { return _fields.end(); }
        auto size() const { return _fields.size(); }
        auto operator[](int e) const { return _fields[e]; }

    private:
        std::string _line;
        std::vector<std::string> _fields{ "" };
    };

    Row _header;
    std::vector<Row> _rows;
    std::string _fileName;
    std::vector<size_t> _fieldPrintWidths;
};
