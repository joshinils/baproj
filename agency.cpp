#include "agency.h"


Agency::Agency(const CSVReader::Row& header, const CSVReader::Row& row)
{
    int rowIndex = 0;
    for(auto title : header)
    {
        if(title == "agency_id") this->agency_id = stoi(row[rowIndex]);
        else if(title == "agency_name")
            this->agency_name = row[rowIndex];
        else if(title == "agency_url")
            this->agency_url = row[rowIndex];
        else if(title == "agency_timezone")
            this->agency_timezone = row[rowIndex];
        else if(title == "agency_lang")
            this->agency_lang = row[rowIndex];
        else if(title == "agency_phone")
            this->agency_phone = row[rowIndex];
        else if(title == "agency_fare_url")
            this->agency_fare_url = row[rowIndex];
        else if(title == "agency_email")
            this->agency_email = row[rowIndex];

        ++rowIndex;
    }
    // std::optional<int> agency_id;
    // std::string agency_name;
    // std::string agency_url;
    // std::string agency_timezone;
    // std::optional<std::string> agency_lang;
    // std::optional<std::string> agency_phone;
    // std::optional<std::string> agency_fare_url;
    // std::optional<std::string> agency_email;
}

Agency::~Agency() { }
