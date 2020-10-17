#pragma once
#include <string>
class Agency
{
public:
    Agency();
    ~Agency();

private:
    /* Full name of the transit agency. */
    std::string agency_name; // Required

    /* URL of the transit agency. */
    std::string agency_url; // Required

    /* Timezone where the transit agency is located. If multiple agencies are specified in the dataset, each must have
     * the same agency_timezone. */
    /* Timezone */ int agency_timezone; // Required

    /* Primary language used by this transit agency. This field helps GTFS consumers choose capitalization rules and
     * other language-specific settings for the dataset. */
    /* Language code */ int agency_lang; // Optional

    /* A voice telephone number for the specified agency. This field is a string value that presents the telephone
     * number as typical for the agency's service area. It can and should contain punctuation marks to group the digits
     * of the number. Dialable text (for example, TriMet's "503-238-RIDE") is permitted, but the field must not contain
     * any other descriptive text. */
    /* Phone number */ int agency_phone; // Optional

    /* URL of a web page that allows a rider to purchase tickets or other fare instruments for that agency online. */
    std::string agency_fare_url; // Optional

    /* Email address actively monitored by the agency’s customer service department. This email address should be a
     * direct contact point where transit riders can reach a customer service representative at the agency. */
    /* Email */ int agency_email; // Optional
};
