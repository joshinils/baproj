#pragma once
#include "CSVReader.h"
#include <iostream>
#include <optional>
#include <string>

class Agency
{
public:
    Agency(std::optional<int> agency_id,
           std::string agency_name,
           std::string agency_url,
           std::string agency_timezone,
           std::optional<std::string> agency_lang,
           std::optional<std::string> agency_phone,
           std::optional<std::string> agency_fare_url,
           std::optional<std::string> agency_email);
    ~Agency();

    friend std::ostream& operator<<(std::ostream& ostr, const Agency& agency)
    {
        if(agency.agency_id.has_value()) ostr << "agency_id:" << agency.agency_id.value() << ", ";
        ostr << "agency_name:" << agency.agency_name << ", ";
        ostr << "agency_url:" << agency.agency_url << ", ";
        ostr << "agency_timezone:" << agency.agency_timezone;
        if(agency.agency_lang.has_value()) ostr << ", agency_lang:" << agency.agency_lang.value();
        if(agency.agency_phone.has_value()) ostr << ", agency_phone:" << agency.agency_phone.value();
        if(agency.agency_fare_url.has_value()) ostr << ", agency_fare_url:" << agency.agency_fare_url.value();
        if(agency.agency_email.has_value()) ostr << ", agency_email:" << agency.agency_email.value();
        return ostr;
    }

private:
    /* Identifies a transit brandwhich is often synonymous with a transit agency. Note that in some cases, such as when
     * a single agency operates multiple separate services, agencies and brands are distinct. This document uses the
     * term "agency" in place of "brand". A dataset may contain data from multiple agencies. This field is required when
     * the dataset contains data for multiple transit agencies, otherwise it is optional.*/
    std::optional<int> agency_id;

    /* Full name of the transit agency. */
    std::string agency_name; // Required

    /* URL of the transit agency. */
    std::string agency_url; // Required

    /* Timezone where the transit agency is located. If multiple agencies are specified in the dataset, each must have
     * the same agency_timezone. */
    std::string agency_timezone; // Required

    /* Primary language used by this transit agency. This field helps GTFS consumers choose capitalization rules and
     * other language-specific settings for the dataset. */
    std::optional<std::string> agency_lang; // Optional

    /* A voice telephone number for the specified agency. This field is a string value that presents the telephone
     * number as typical for the agency's service area. It can and should contain punctuation marks to group the digits
     * of the number. Dialable text (for example, TriMet's "503-238-RIDE") is permitted, but the field must not contain
     * any other descriptive text. */
    std::optional<std::string> agency_phone; // Optional

    /* URL of a web page that allows a rider to purchase tickets or other fare instruments for that agency online. */
    std::optional<std::string> agency_fare_url; // Optional

    /* Email address actively monitored by the agency’s customer service department. This email address should be a
     * direct contact point where transit riders can reach a customer service representative at the agency. */
    std::optional<std::string> agency_email; // Optional
};
