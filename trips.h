#pragma once
//#include "GTFS.h"
#include "routes.h"
#include "stop_times.h"
#include "type_aliases.h"
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Stop_times;

class Trips
{
public:
    enum class direction_id_enum
    {
        Unset    = -1, // this field is optional
        Outbound = 0, //Travel in one direction (e.g. outbound travel).
        Inbound  = 1, // Travel in the opposite direction (e.g. inbound travel).
    };

    enum class wheelchair_accessible_enum
    {
        Unset         = -1, // this field is optional
        NoInfo        = 0, // No accessibility information for the trip.
        Wheelchair    = 1, // Vehicle being used on this trip can accommodate at least one rider in a wheelchair.
        NoWheelchairs = 2, // No riders in wheelchairs can be accommodated on this trip.
    };

    enum class bikes_allowed_enum
    {
        Unset      = -1, // this field is optional
        NoInfo     = 0, // No bike information for the trip.
        Bicycle    = 1, // Vehicle being used on this particular trip can accommodate at least one bicycle.
        NoBicycles = 2, // No bicycles are allowed on this trip.
    };

    Trips(std::string route_id,
          int service_id,
          int trip_id,
          std::optional<std::string> trip_headsign,
          std::optional<std::string> trip_short_name,
          direction_id_enum direction_id,
          std::optional<int> block_id,
          std::optional<int> shape_id,
          wheelchair_accessible_enum wheelchair_accessible,
          bikes_allowed_enum bikes_allowed);
    ~Trips();

    /* Identifies a route.
     * ID referencing routes.route_id */
    std::string getRoute_id() const { return route_id; }

    /* Identifies a set of dates when service is available for one or more routes.
     * ID referencing calendar.service_id or calendar_dates.service_id */
    int getService_id() const { return service_id; }

    /* Identifies a trip. */
    int getTrip_id() const { return trip_id; }

    /* Text that appears on signage identifying the trip's destination to riders. Use this field to distinguish
     * between different patterns of service on the same route. If the headsign changes during a trip, trip_headsign can
     * be overridden by specifying values for the stop_times.stop_headsign. */
    std::optional<std::string> getTrip_headsign() const { return trip_headsign; }

    /* Public facing text used to identify the trip to riders, for instance, to identify train numbers for commuter
     * rail trips. If riders do not commonly rely on trip names, leave this field empty. A trip_short_name value, if
     * provided, should uniquely identify a trip within a service day; it should not be used for destination names or
     * limited/express designations. */
    std::optional<std::string> getTrip_short_name() const { return trip_short_name; }

    /* Indicates the direction of travel for a trip. This field is not used in routing; it provides a way to separate
    trips by direction when publishing time tables. Valid options are:

        0 - Travel in one direction (e.g. outbound travel).
        1 - Travel in the opposite direction (e.g. inbound travel).

    Example: The trip_headsign and direction_id fields could be used together to assign a name to travel in each
    direction for a set of trips. A trips.txt file could contain these records for use in time tables:
        trip_id,...,trip_headsign,direction_id
        1234,...,Airport,0
        1505,...,Downtown,1 */
    direction_id_enum getDirection_id() const { return direction_id; }

    /* Identifies the block to which the trip belongs. A block consists of a single trip or many sequential trips made
     * using the same vehicle, defined by shared service days and block_id. A block_id can have trips with different
     * service days, making distinct blocks. See the example below */
    std::optional<int> getBlock_id() const { return block_id; }

    /* Identifies a geospatial shape that describes the vehicle travel path for a trip.

    Conditionally required:
     This field is required if the trip has continuous behavior defined, either at the route level or at the stop time
     level.
    Otherwise, it's optional.
     * ID referencing shapes.shape_id
     * Conditionally required */
    std::optional<int> getShape_id() const { return shape_id; }

    /* Indicates wheelchair accessibility. Valid options are:

        0 or empty - No accessibility information for the trip.
        1 - Vehicle being used on this particular trip can accommodate at least one rider in a wheelchair.
        2 - No riders in wheelchairs can be accommodated on this trip. */
    wheelchair_accessible_enum getWheelchair_accessible() const { return wheelchair_accessible; }

    /* Indicates whether bikes are allowed. Valid options are:

        0 or empty - No bike information for the trip.
        1 - Vehicle being used on this particular trip can accommodate at least one bicycle.
        2 - No bicycles are allowed on this trip. */
    bikes_allowed_enum getBikes_allowed() const { return bikes_allowed; }

    friend std::ostream& operator<<(std::ostream& ostr, const Trips& trips)
    {
        ostr << "route_id: " << trips.route_id;
        ostr << ", service_id: " << trips.service_id;
        ostr << ", trip_id: " << trips.trip_id;
        if(trips.trip_headsign.has_value()) ostr << ", trip_headsign: " << trips.trip_headsign.value();
        if(trips.trip_short_name.has_value()) ostr << ", trip_short_name: " << trips.trip_short_name.value();
        ostr << ", direction_id: " << static_cast<int>(trips.direction_id);
        if(trips.block_id.has_value()) ostr << ", block_id: " << trips.block_id.value();
        if(trips.shape_id.has_value()) ostr << ", shape_id: " << trips.shape_id.value();
        ostr << ", wheelchair_accessible: " << static_cast<int>(trips.wheelchair_accessible);
        ostr << ", bikes_allowed: " << static_cast<int>(trips.bikes_allowed);
        return ostr;
    }

private:
    /* Identifies a route.
     * ID referencing routes.route_id */
    std::string route_id;
    std::weak_ptr<Routes> route = std::weak_ptr<Routes>();
    friend class GTFS;

    /* Identifies a set of dates when service is available for one or more routes.
     * ID referencing calendar.service_id or calendar_dates.service_id */
    int service_id;

    /* Identifies a trip. */
    int trip_id;

    /* Text that appears on signage identifying the trip's destination to riders. Use this field to distinguish
     * between different patterns of service on the same route. If the headsign changes during a trip, trip_headsign can
     * be overridden by specifying values for the stop_times.stop_headsign. */
    std::optional<std::string> trip_headsign;

    /* Public facing text used to identify the trip to riders, for instance, to identify train numbers for commuter
     * rail trips. If riders do not commonly rely on trip names, leave this field empty. A trip_short_name value, if
     * provided, should uniquely identify a trip within a service day; it should not be used for destination names or
     * limited/express designations. */
    std::optional<std::string> trip_short_name;

    /* Indicates the direction of travel for a trip. This field is not used in routing; it provides a way to separate
    trips by direction when publishing time tables. Valid options are:

        0 - Travel in one direction (e.g. outbound travel).
        1 - Travel in the opposite direction (e.g. inbound travel).

    Example: The trip_headsign and direction_id fields could be used together to assign a name to travel in each
    direction for a set of trips. A trips.txt file could contain these records for use in time tables:
        trip_id,...,trip_headsign,direction_id
        1234,...,Airport,0
        1505,...,Downtown,1 */
    direction_id_enum direction_id = direction_id_enum::Unset;

    /* Identifies the block to which the trip belongs. A block consists of a single trip or many sequential trips made
     * using the same vehicle, defined by shared service days and block_id. A block_id can have trips with different
     * service days, making distinct blocks. See the example below */
    std::optional<int> block_id;

    /* Identifies a geospatial shape that describes the vehicle travel path for a trip.

    Conditionally required:
     This field is required if the trip has continuous behavior defined, either at the route level or at the stop time
     level.
    Otherwise, it's optional.
     * ID referencing shapes.shape_id
     * Conditionally required */
    std::optional<int> shape_id;

    /* Indicates wheelchair accessibility. Valid options are:

        0 or empty - No accessibility information for the trip.
        1 - Vehicle being used on this particular trip can accommodate at least one rider in a wheelchair.
        2 - No riders in wheelchairs can be accommodated on this trip. */
    wheelchair_accessible_enum wheelchair_accessible = wheelchair_accessible_enum::Unset;

    /* Indicates whether bikes are allowed. Valid options are:

        0 or empty - No bike information for the trip.
        1 - Vehicle being used on this particular trip can accommodate at least one bicycle.
        2 - No bicycles are allowed on this trip. */
    bikes_allowed_enum bikes_allowed = bikes_allowed_enum::Unset;


    /***
     * additional data not from read files
     * ***/

    // store the stop_time instances which reference this trip
    std::map<stop_sequence_t, std::weak_ptr<Stop_times>> includedStopTimes;
};
