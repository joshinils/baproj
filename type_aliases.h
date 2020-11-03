#include "TimePoint.h"

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
} // namespace stop_times_types
