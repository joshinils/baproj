#include "stop.h"

Stop::Stop(std::string stop_id,
           std::optional<std::string> stop_code,
           std::optional<std::string> stop_name,
           std::optional<std::string> stop_desc,
           std::optional<double> stop_lat,
           std::optional<double> stop_lon,
           std::optional<std::string> zone_id,
           std::optional<std::string> stop_url,
           location_type_enum location_type,
           std::optional<long long> parent_station,
           std::optional<std::string> stop_timezone,
           wheelchair_boarding_enum wheelchair_boarding,
           std::optional<int> level_id,
           std::optional<std::string> platform_code)
    : stop_id(stop_id)
    , stop_code(stop_code)
    , stop_name(stop_name)
    , stop_desc(stop_desc)
    , stop_lat(stop_lat)
    , stop_lon(stop_lon)
    , zone_id(zone_id)
    , stop_url(stop_url)
    , location_type(location_type)
    , parent_station(parent_station)
    , stop_timezone(stop_timezone)
    , wheelchair_boarding(wheelchair_boarding)
    , level_id(level_id)
    , platform_code(platform_code)
{ }

Stop::~Stop() { }
