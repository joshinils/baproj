#include "stop_times.h"

Stop_times::Stop_times(int trip_id,
                       std::optional<std::string> arrival_time,
                       std::optional<std::string> departure_time,
                       std::string stop_id,
                       unsigned int stop_sequence,
                       std::optional<std::string> stop_headsign,
                       pickup_type_enum pickup_type,
                       drop_off_type_enum drop_off_type,
                       continuous_pickup_enum continuous_pickup,
                       continuous_drop_off_enum continuous_drop_off,
                       std::optional<double> shape_dist_traveled,
                       timepoint_enum timepoint)
    : trip_id(trip_id)
    , arrival_time(arrival_time)
    , departure_time(departure_time)
    , stop_id(stop_id)
    , stop_sequence(stop_sequence)
    , stop_headsign(stop_headsign)
    , pickup_type(pickup_type)
    , drop_off_type(drop_off_type)
    , continuous_pickup(continuous_pickup)
    , continuous_drop_off(continuous_drop_off)
    , shape_dist_traveled(shape_dist_traveled)
    , timepoint(timepoint)
{
    // int trip_id;
    // std::optional<std::string> arrival_time;
    // std::optional<std::string> departure_time;
    // std::string stop_id;
    // unsigned int stop_sequence;
    // std::optional<std::string> stop_headsign;
    // pickup_type_enum pickup_type;
    // drop_off_type_enum drop_off_type;
    // continuous_pickup_enum continuous_pickup;
    // continuous_drop_off_enum continuous_drop_off;
    // std::optional<double> shape_dist_traveled;
    // timepoint_enum timepoint;
}

Stop_times::~Stop_times() { }
