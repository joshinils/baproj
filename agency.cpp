#include "agency.h"


Agency::Agency(std::optional<int> agency_id,
               std::string agency_name,
               std::string agency_url,
               std::string agency_timezone,
               std::optional<std::string> agency_lang,
               std::optional<std::string> agency_phone,
               std::optional<std::string> agency_fare_url,
               std::optional<std::string> agency_email)
    : agency_id(agency_id)
    , agency_name(agency_name)
    , agency_url(agency_url)
    , agency_timezone(agency_timezone)
    , agency_lang(agency_lang)
    , agency_phone(agency_phone)
    , agency_fare_url(agency_fare_url)
    , agency_email(agency_email)
{
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
