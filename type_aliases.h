#include "TimePoint.h"
#include <optional>
#include <string>

namespace stop_times_types
{
    using trip_id_t        = int;
    using arrival_time_t   = std::optional<TimePoint>;
    using departure_time_t = std::optional<TimePoint>;
    using stop_id_t        = std::string;
    using stop_sequence_t  = unsigned int;
    using stop_headsign_t  = std::optional<std::string>;
    //using pickup_type_t         = pickup_type_enum;
    //using drop_off_type_t       = drop_off_type_enum;
    //using continuous_pickup_t   = continuous_pickup_enum;
    //using continuous_drop_off_t = continuous_drop_off_enum;
    using shape_dist_traveled_t = std::optional<double>;
    //using timepoint_t           = timepoint_enum;
} /// namespace stop_times_types

namespace stop_types
{
    using stop_id_t   = std::string;
    using stop_code_t = std::optional<std::string>;
    using stop_name_t = std::optional<std::string>;
    using stop_desc_t = std::optional<std::string>;
    using stop_lat_t  = std::optional<double>;
    using stop_lon_t  = std::optional<double>;
    using zone_id_t   = std::optional<std::string>;
    using stop_url_t  = std::optional<std::string>;
    //using location_type_t = location_type_enum;
    using parent_station_t = std::optional<long long>;
    using stop_timezone_t  = std::optional<std::string>;
    //using wheelchair_boarding_t = wheelchair_boarding_enum;
    using level_id_t      = std::optional<int>;
    using platform_code_t = std::optional<std::string>;
} /// namespace stop_types

namespace trip_types
{
    using route_id_t        = std::string;
    using service_id_t      = int;
    using trip_id_t         = int;
    using trip_headsign_t   = std::optional<std::string>;
    using trip_short_name_t = std::optional<std::string>;
    //using direction_id_t = direction_id_enum;
    using block_id_t = std::optional<int>;
    using shape_id_t = std::optional<int>;
    //using wheelchair_accessible_t = wheelchair_accessible_enum;
    //using bikes_allowed_t = bikes_allowed_enum;

} /// namespace trip_types
