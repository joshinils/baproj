#include "stop.h"
#include "type_aliases.h"

using namespace stop_types;

Stop::Stop(stop_id_t stop_id,
           stop_code_t stop_code,
           stop_name_t stop_name,
           stop_desc_t stop_desc,
           stop_lat_t stop_lat,
           stop_lon_t stop_lon,
           zone_id_t zone_id,
           stop_url_t stop_url,
           location_type_enum location_type,
           parent_station_t parent_station,
           stop_timezone_t stop_timezone,
           wheelchair_boarding_enum wheelchair_boarding,
           level_id_t level_id,
           platform_code_t platform_code)
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
