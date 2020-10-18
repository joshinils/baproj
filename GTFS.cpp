#include "GTFS.h"
#include "CSVReader.h"
#include <filesystem>

GTFS::GTFS(const std::string& folder)
{
    if(std::filesystem::exists(folder + "/agency.txt"))
    {
        CSVReader agency(folder + "/agency.txt");
        agency.printCSV();

        bool hasAgencyId      = false;
        bool hasAgencyLang    = false;
        bool hasAgencyPhone   = false;
        bool hasAgencyFareUrl = false;
        bool hasAgencyEmail   = false;

        int agencyIdIdx       = -1;
        int agencyNameIdx     = -1;
        int agencyUrlIdx      = -1;
        int agencyTimezoneIdx = -1;
        int agencyLangIdx     = -1;
        int agencyPhoneIdx    = -1;
        int agencyFareUrlIdx  = -1;
        int agencyEmailIdx    = -1;

        int colIndex = 0;
        for(const auto& e : agency.getHeader())
        {
            if(!hasAgencyId && e == "agency_id")
            {
                hasAgencyId = true;
                agencyIdIdx = colIndex;
            }
            else if(e == "agency_name")
            {
                agencyNameIdx = colIndex;
            }
            else if(e == "agency_url")
            {
                agencyUrlIdx = colIndex;
            }
            else if(e == "agency_timezone")
            {
                agencyTimezoneIdx = colIndex;
            }
            else if(!hasAgencyLang && e == "agency_lang")
            {
                hasAgencyLang = true;
                agencyLangIdx = colIndex;
            }
            else if(!hasAgencyPhone && e == "agency_phone")
            {
                hasAgencyPhone = true;
                agencyPhoneIdx = colIndex;
            }
            else if(!hasAgencyFareUrl && e == "agency_fare_url")
            {
                hasAgencyFareUrl = true;
                agencyFareUrlIdx = colIndex;
            }
            else if(!hasAgencyEmail && e == "agency_email")
            {
                hasAgencyEmail = true;
                agencyEmailIdx = colIndex;
            }

            ++colIndex;
        }

        for(auto row : agency)
        {
            this->agency.push_back(Agency(hasAgencyId ? std::stoi(row[agencyIdIdx]) : std::optional<int>(),
                                          row[agencyNameIdx],
                                          row[agencyUrlIdx],
                                          row[agencyTimezoneIdx],
                                          hasAgencyLang ? row[agencyLangIdx] : std::optional<std::string>(),
                                          hasAgencyPhone ? row[agencyPhoneIdx] : std::optional<std::string>(),
                                          hasAgencyFareUrl ? row[agencyFareUrlIdx] : std::optional<std::string>(),
                                          hasAgencyEmail ? row[agencyEmailIdx] : std::optional<std::string>()));
        }
        for(auto row : this->agency) std::cout << row << std::endl;
    }
    else
    {
        throw std::string(folder + "/agency.txt not found!");
    }

    if(std::filesystem::exists(folder + "/stops.txt"))
    {
        CSVReader stops(folder + "/stops.txt");
        stops.printCSV();

        //int                               stop_id;
        //std::optional<std::string>        stop_code;
        //std::optional<std::string>        stop_name;
        //std::optional<std::string>        stop_desc;
        //std::optional<double>             stop_lat;
        //std::optional<double>             stop_lon;
        //std::optional<int>                zone_id;
        //std::optional<std::string>        stop_url;
        //Stops::location_type_enum         location_type;
        //std::optional<int>                parent_station;
        //std::optional<std::string>        stop_timezone;
        //Stops::wheelchair_boarding_enum   wheelchair_boarding;
        //std::optional<int>                level_id;
        //std::optional<std::string>        platform_code;

        bool hasStop_code           = false;
        bool hasStop_name           = false;
        bool hasStop_desc           = false;
        bool hasStop_lat            = false;
        bool hasStop_lon            = false;
        bool hasZone_id             = false;
        bool hasStop_url            = false;
        bool hasLocation_type       = false;
        bool hasParent_station      = false;
        bool hasStop_timezone       = false;
        bool hasWheelchair_boarding = false;
        bool hasLevel_id            = false;
        bool hasPlatform_code       = false;

        int stop_idIdx             = -1;
        int stop_codeIdx           = -1;
        int stop_nameIdx           = -1;
        int stop_descIdx           = -1;
        int stop_latIdx            = -1;
        int stop_lonIdx            = -1;
        int zone_idIdx             = -1;
        int stop_urlIdx            = -1;
        int location_typeIdx       = -1;
        int parent_stationIdx      = -1;
        int stop_timezoneIdx       = -1;
        int wheelchair_boardingIdx = -1;
        int level_idIdx            = -1;
        int platform_codeIdx       = -1;

        int colIndex = 0;
        for(const auto& e : stops.getHeader())
        {
            if(e == "stop_id") { stop_idIdx = colIndex; }
            // TODO adjust copy paste to stops from agency:

            // else if(e == "stops_name")
            // {
            //     stopsNameIdx = colIndex;
            // }
            // else if(e == "stops_url")
            // {
            //     stopsUrlIdx = colIndex;
            // }
            // else if(e == "stops_timezone")
            // {
            //     stopsTimezoneIdx = colIndex;
            // }
            // else if(!hasStopsLang && e == "stops_lang")
            // {
            //     hasStopsLang = true;
            //     stopsLangIdx = colIndex;
            // }
            // else if(!hasStopsPhone && e == "stops_phone")
            // {
            //     hasStopsPhone = true;
            //     stopsPhoneIdx = colIndex;
            // }
            // else if(!hasStopsFareUrl && e == "stops_fare_url")
            // {
            //     hasStopsFareUrl = true;
            //     stopsFareUrlIdx = colIndex;
            // }
            // else if(!hasStopsEmail && e == "stops_email")
            // {
            //     hasStopsEmail = true;
            //     stopsEmailIdx = colIndex;
            // }

            ++colIndex;
        }

        for(auto row : stops)
        {
            this->stops.emplace_back(Stops(std::stoi(row[stop_idIdx]),
                                           hasStop_code ? row[stop_codeIdx] : std::optional<std::string>(),
                                           hasStop_name ? row[stop_nameIdx] : std::optional<std::string>(),
                                           hasStop_desc ? row[stop_descIdx] : std::optional<std::string>(),
                                           hasStop_lat ? std::stod(row[stop_latIdx]) : std::optional<double>(),
                                           hasStop_lon ? std::stod(row[stop_lonIdx]) : std::optional<double>(),
                                           hasZone_id ? std::stoi(row[zone_idIdx]) : std::optional<int>(),
                                           hasStop_url ? row[stop_urlIdx] : std::optional<std::string>(),
                                           hasLocation_type ? Stops::location_type_enum(stoi(row[location_typeIdx]))
                                                            : Stops::location_type_enum::Unset,
                                           hasParent_station ? std::stoi(row[parent_stationIdx]) : std::optional<int>(),
                                           hasStop_timezone ? row[stop_timezoneIdx] : std::optional<std::string>(),
                                           hasWheelchair_boarding
                                           ? Stops::wheelchair_boarding_enum(std::stoi(row[wheelchair_boardingIdx]))
                                           : Stops::wheelchair_boarding_enum::Unset,
                                           hasLevel_id ? std::stoi(row[level_idIdx]) : std::optional<int>(),
                                           hasPlatform_code ? row[platform_codeIdx] : std::optional<std::string>()));
        }
        //TODO write output operator for stops
        //for(auto row : this->stops) std::cout << row << std::endl;
    }
    else
    {
        throw std::string(folder + "/stops.txt not found!");
    }


    if(std::filesystem::exists(folder + "/routes.txt"))
    {
        CSVReader routes(folder + "/routes.txt");
        routes.printCSV();
        routes;
    }
    else
    {
        throw std::string(folder + "/routes.txt not found!");
    }


    if(std::filesystem::exists(folder + "/trips.txt"))
    {
        CSVReader trips(folder + "/trips.txt");
        trips.printCSV();
        trips;
    }
    else
    {
        throw std::string(folder + "/trips.txt not found!");
    }


    if(std::filesystem::exists(folder + "/stop_times.txt"))
    {
        CSVReader stop_times(folder + "/stop_times.txt");
        stop_times.printCSV();
        stop_times;
    }
    else
    {
        throw std::string(folder + "/stop_times.txt not found!");
    }


    if(std::filesystem::exists(folder + "/calendar.txt"))
    {
        CSVReader calendar(folder + "/calendar.txt");
        calendar.printCSV();
        calendar;
    }

    if(std::filesystem::exists(folder + "/calendar_dates.txt"))
    {
        CSVReader calendar_dates(folder + "/calendar_dates.txt");
        calendar_dates.printCSV();
        calendar_dates;
    }

    if(std::filesystem::exists(folder + "/fare_rules.txt"))
    {
        CSVReader fare_rules(folder + "/fare_rules.txt");
        fare_rules.printCSV();
        fare_rules;
    }

    if(std::filesystem::exists(folder + "/fare_attributes.txt"))
    {
        CSVReader fare_attributes(folder + "/fare_attributes.txt");
        fare_attributes.printCSV();
        fare_attributes;
    }

    if(std::filesystem::exists(folder + "/shapes.txt"))
    {
        CSVReader shapes(folder + "/shapes.txt");
        shapes.printCSV();
        shapes;
    }

    if(std::filesystem::exists(folder + "/frequencies.txt"))
    {
        CSVReader frequencies(folder + "/frequencies.txt");
        frequencies.printCSV();
        frequencies;
    }

    if(std::filesystem::exists(folder + "/transfers.txt"))
    {
        CSVReader transfers(folder + "/transfers.txt");
        transfers.printCSV();
        transfers;
    }

    if(std::filesystem::exists(folder + "/pathways.txt"))
    {
        CSVReader pathways(folder + "/pathways.txt");
        pathways.printCSV();
        pathways;
    }

    if(std::filesystem::exists(folder + "/levels.txt"))
    {
        CSVReader levels(folder + "/levels.txt");
        levels.printCSV();
        levels;
    }

    if(std::filesystem::exists(folder + "/feed_info.txt"))
    {
        CSVReader feed_info(folder + "/feed_info.txt");
        feed_info.printCSV();
        feed_info;
    }
}

GTFS::~GTFS() { }
