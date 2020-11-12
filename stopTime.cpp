#include "stopTime.h"
using namespace stop_times_types;

StopTime::StopTime(trip_id_t trip_id,
                   arrival_time_t arrival_time,
                   departure_time_t departure_time,
                   stop_id_t stop_id,
                   stop_sequence_t stop_sequence,
                   stop_headsign_t stop_headsign,
                   pickup_type_enum pickup_type,
                   drop_off_type_enum drop_off_type,
                   continuous_pickup_enum continuous_pickup,
                   continuous_drop_off_enum continuous_drop_off,
                   shape_dist_traveled_t shape_dist_traveled,
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

StopTime::~StopTime() { }
