#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


class CSVReader
{
public:
    class Row
    {
        friend CSVReader;

    public:
        Row() = default;
        Row(const std::string& line);

        ~Row() = default;

        /// std::string getLine() { return _line; }
        auto begin() const { return _fields.begin(); }
        auto end() const { return _fields.end(); }
        auto size() const { return _fields.size(); }
        auto operator[](int e) const { return _fields[e]; }
        friend std::ostream& operator<<(std::ostream& ostr, const Row& r)
        {
            for(size_t i = 0; i < r._fields.size(); i++)
            {
                ostr << r._fields[i];
                if(i < r._fields.size() + 1) ostr << ", ";
            }

            return ostr;
        }

    private:
        /// std::string _line;
        std::vector<std::string> _fields{ "" };
    };

public:
    CSVReader(std::string filename);
    ~CSVReader();

    auto begin() const { return _rows.begin(); }
    auto end() const { return _rows.end(); }

    const Row& getHeader() const { return _header; }
    size_t rowCount() const { return _rows.size(); }
    std::string getFilename() const { return _fileName; }

    size_t getPrintWidth(size_t fieldId) const { return _fieldPrintWidths.at(fieldId); }

    void printCSV() const;

private:
    static const int max_row_read;
    Row _header;
    std::vector<Row> _rows;
    std::string _fileName;
    std::vector<size_t> _fieldPrintWidths;
};
