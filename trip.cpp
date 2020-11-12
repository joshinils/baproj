#include "trip.h"

Trip::Trip(std::string route_id,
           int service_id,
           int trip_id,
           std::optional<std::string> trip_headsign,
           std::optional<std::string> trip_short_name,
           direction_id_enum direction_id,
           std::optional<int> block_id,
           std::optional<int> shape_id,
           wheelchair_accessible_enum wheelchair_accessible,
           bikes_allowed_enum bikes_allowed)
    : route_id(route_id)
    , service_id(service_id)
    , trip_id(trip_id)
    , trip_headsign(trip_headsign)
    , trip_short_name(trip_short_name)
    , direction_id(direction_id)
    , block_id(block_id)
    , shape_id(shape_id)
    , wheelchair_accessible(wheelchair_accessible)
    , bikes_allowed(bikes_allowed)
{
    // std::string route_id;
    // int service_id;
    // int trip_id;
    // std::optional<std::string> trip_headsign;
    // std::optional<std::string> trip_short_name;
    // direction_id_enum direction_id;
    // std::optional<int> block_id;
    // std::optional<int> shape_id;
    // wheelchair_accessible_enum wheelchair_accessible;
    // bikes_allowed_enum bikes_allowed;
}

Trip::~Trip() { }
