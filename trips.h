#pragma once
#include <string>

class Trips
{
public:
    Trips();
    ~Trips();

private:
    /* Identifies a route. */
    /* ID referencing routes.route_id */ int route_id; // Required

    /* Identifies a set of dates when service is available for one or more routes. */
    /* ID referencing calendar.service_id or calendar_dates.service_id */ int service_id; // Required

    /* Identifies a trip. */
    int trip_id; // Required

    /* Text that appears on signage identifying the trip's destination to riders. Use this field to distinguish
     * between different patterns of service on the same route. If the headsign changes during a trip, trip_headsign can
     * be overridden by specifying values for the stop_times.stop_headsign. */
    std::string trip_headsign; // Optional

    /* Public facing text used to identify the trip to riders, for instance, to identify train numbers for commuter
     * rail trips. If riders do not commonly rely on trip names, leave this field empty. A trip_short_name value, if
     * provided, should uniquely identify a trip within a service day; it should not be used for destination names or
     * limited/express designations. */
    std::string trip_short_name; // Optional

    /* Indicates the direction of travel for a trip. This field is not used in routing; it provides a way to separate
    trips by direction when publishing time tables. Valid options are:

    0 - Travel in one direction (e.g. outbound travel).
    1 - Travel in the opposite direction (e.g. inbound travel).Example: The trip_headsign and direction_id fields could be used together to assign a name to travel in each direction for a set of trips. A trips.txt file could contain these records for use in time tables:
     trip_id,...,trip_headsign,direction_id
     1234,...,Airport,0
     1505,...,Downtown,1*/
    enum class direction_id_enum
    {
        Unset, // this field is optional
        Outbound = 0, //Travel in one direction (e.g. outbound travel).
        Inbound  = 1, // Travel in the opposite direction (e.g. inbound travel).
    };
    direction_id_enum direction_id = direction_id_enum::Unset; // Optional

    /* Identifies the block to which the trip belongs. A block consists of a single trip or many sequential trips made
     * using the same vehicle, defined by shared service days and block_id. A block_id can have trips with different
     * service days, making distinct blocks. See the example below */
    int block_id; // Optional

    /* Identifies a geospatial shape that describes the vehicle travel path for a trip.

    Conditionally required:
     This field is required if the trip has continuous behavior defined, either at the route level or at the stop time level.
    Otherwise, it's optional.*/
    /* ID referencing shapes.shape_id */ int shape_id; // Conditionally required

    /* Indicates wheelchair accessibility. Valid options are:

    0 or empty - No accessibility information for the trip.
    1 - Vehicle being used on this particular trip can accommodate at least one rider in a wheelchair.
    2 - No riders in wheelchairs can be accommodated on this trip.*/
    enum class wheelchair_accessible_enum
    {
        Unset, // this field is optional
        NoInfo        = 0, // No accessibility information for the trip.
        Wheelchair    = 1, // Vehicle being used on this trip can accommodate at least one rider in a wheelchair.
        NoWheelchairs = 2, // No riders in wheelchairs can be accommodated on this trip.
    };
    wheelchair_accessible_enum wheelchair_accessible = wheelchair_accessible_enum::Unset; // Optional

    /* Indicates whether bikes are allowed. Valid options are:

    0 or empty - No bike information for the trip.
    1 - Vehicle being used on this particular trip can accommodate at least one bicycle.
    2 - No bicycles are allowed on this trip.*/
    enum class bikes_allowed_enum
    {
        Unset, // this field is optional
        NoInfo     = 0, // No bike information for the trip.
        Bicycle    = 1, // Vehicle being used on this particular trip can accommodate at least one bicycle.
        NoBicycles = 2, // No bicycles are allowed on this trip.*/
    };
    bikes_allowed_enum bikes_allowed = bikes_allowed_enum::Unset; // Optional
};
