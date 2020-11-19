#pragma once
#include "trip.h"
#include "type_aliases.h"
#include <iostream>
#include <memory>
#include <optional>
#include <string>

class Trip;
class Stop;

class StopTime
{
public:
    enum class pickup_type_enum
    {
        Unset        = -1, // this field is optional
        Pickup       = 0, // or empty - Regularly scheduled pickup.
        NonPickup    = 1, // No pickup available.
        PhonePickup  = 2, // Must phone agency to arrange pickup.
        DriverPickup = 3, // Must coordinate with driver to arrange pickup.
    };

    enum class drop_off_type_enum
    {
        Unset         = -1, // this field is optional
        DropOff       = 0,
        NonDropOff    = 1,
        PhoneDropOff  = 2,
        DriverDropOff = 3,
    };

    enum class continuous_pickup_enum
    {
        Unset            = -1, // this field is optional
        Continuous       = 0,
        NonContinuous    = 1,
        PhoneContinuous  = 2,
        DriverContinuous = 3,
    };

    enum class continuous_drop_off_enum
    {
        Unset            = -1, // this field is optional
        Continuous       = 0,
        NonContinuous    = 1,
        PhoneContinuous  = 2,
        DriverContinuous = 3,
    };

    enum class timepoint_enum
    {
        Unset       = -1, // this field is optional
        Approximate = 0, // Times are considered approximate.
        Exact       = 1, // or empty - Times are considered exact.*/
    };

    StopTime(stop_times_types::trip_id_t trip_id,
             stop_times_types::arrival_time_t arrival_time,
             stop_times_types::departure_time_t departure_time,
             stop_times_types::stop_id_t stop_id,
             stop_times_types::stop_sequence_t stop_sequence,
             stop_times_types::stop_headsign_t stop_headsign,
             pickup_type_enum pickup_type,
             drop_off_type_enum drop_off_type,
             continuous_pickup_enum continuous_pickup,
             continuous_drop_off_enum continuous_drop_off,
             stop_times_types::shape_dist_traveled_t shape_dist_traveled,
             timepoint_enum timepoint);
    ~StopTime();

    /* Identifies a trip. */
    /* ID referencing trips.trip_id */
    stop_times_types::trip_id_t getTrip_id() const { return trip_id; }

    /* Arrival time at a specific stop for a specific trip on a route. If there are not separate times for arrival and
    departure at a stop, enter the same value for arrival_time and departure_time. For times occurring after midnight on
    the service day, enter the time as a value greater than 24:00:00 in HH:MM:SS local time for the day on which the
    trip schedule begins.

    Scheduled stops where the vehicle strictly adheres to the specified arrival and departure times are timepoints. If
    this stop is not a timepoint, it is recommended to provide an estimated or interpolated time. If this is not
    available, arrival_time can be left empty. Further, indicate that interpolated times are provided with timepoint=0.
    If interpolated times are indicated with timepoint=0, then time points must be indicated with timepoint=1. Provide
    arrival times for all stops that are time points. An arrival time must be specified for the first and the last stop
    in a trip.*
     * Time *
     * Conditionally required */
    stop_times_types::arrival_time_t getArrival_time() const { return arrival_time; }

    /* Departure time from a specific stop for a specific trip on a route. For times occurring after midnight on the
     service day, enter the time as a value greater than 24:00:00 in HH:MM:SS local time for the day on which the trip
     schedule begins. If there are not separate times for arrival and departure at a stop, enter the same value for
     arrival_time and departure_time. See the arrival_time description for more details about using timepoints
     correctly.

     The departure_time field should specify time values whenever possible, including non-binding estimated or
     interpolated times between timepoints.*
     * Time *
     * Conditionally required */
    stop_times_types::departure_time_t getDeparture_time() const { return departure_time; }

    /* Identifies the serviced stop. All stops serviced during a trip must have a record in stop_times.txt. Referenced
     * locations must be stops, not stations or station entrances. A stop may be serviced multiple times in the same
     * trip, and multiple trips and routes may service the same stop.
     * ID referencing stops.stop_id */
    stop_times_types::stop_id_t getStop_id() const { return stop_id; }

    /* Order of stops for a particular trip. The values must increase along the trip but do not need to be
     * consecutive.Example: The first location on the trip could have a stop_sequence=1, the second location on the trip
     * could have a stop_sequence=23, the third location could have a stop_sequence=40, and so on. */
    stop_times_types::stop_sequence_t getStop_sequence() const { return stop_sequence; }

    /* Text that appears on signage identifying the trip's destination to riders. This field overrides the default
     trips.trip_headsign when the headsign changes between stops. If the headsign is displayed for an entire trip, use
     trips.trip_headsign instead.

     A stop_headsign value specified for one stop_time does not apply to subsequent stop_times in the same trip. If you
     want to override the trip_headsign for multiple stop_times in the same trip, the stop_headsign value must be
     repeated in each stop_time row.*/
    stop_times_types::stop_headsign_t getStop_headsign() const { return stop_headsign; }

    /* Indicates pickup method. Valid options are:

        0 or empty - Regularly scheduled pickup.
        1 - No pickup available.
        2 - Must phone agency to arrange pickup.
        3 - Must coordinate with driver to arrange pickup.*/
    pickup_type_enum getPickup_type() const { return pickup_type; }

    /* Indicates drop off method. Valid options are:

        0 or empty - Regularly scheduled drop off.
        1 - No drop off available.
        2 - Must phone agency to arrange drop off.
        3 - Must coordinate with driver to arrange drop off.*/
    drop_off_type_enum getDrop_off_type() const { return drop_off_type; }

    /* Indicates whether a rider can board the transit vehicle at any point along the vehicle’s travel path. The path
    is described by shapes.txt, from this stop_time to the next stop_time in the trip’s stop_sequence. Valid options
    are:

        0 - Continuous stopping pickup.
        1 or empty - No continuous stopping pickup.
        2 - Must phone an agency to arrange continuous pickup.
        3 - Must coordinate with a driver to arrange continuous stopping pickup.

    The continuous pickup behavior indicated in stop_times.txt overrides any behavior defined in routes.txt.*/
    continuous_pickup_enum getContinuous_pickup() const { return continuous_pickup; }

    /* Indicates whether a rider can alight from the transit vehicle at any point along the vehicle’s travel path as
    described by shapes.txt, from this stop_time to the next stop_time in the trip’s stop_sequence.

        0 - Continuous stopping drop off.
        1 or empty - No continuous stopping drop off.
        2 - Must phone an agency to arrange continuous drop off.
        3 - Must coordinate with a driver to arrange continuous stopping drop off.

    The continuous drop-off behavior indicated in stop_times.txt overrides any behavior defined in routes.txt.*/
    continuous_drop_off_enum getContinuous_drop_off() const { return continuous_drop_off; }

    /* Actual distance traveled along the associated shape, from the first stop to the stop specified in this record.
     * This field specifies how much of the shape to draw between any two stops during a trip. Must be in the same units
     * used in shapes.txt. Values used for shape_dist_traveled must increase along with stop_sequence; they cannot be
     * used to show reverse travel along a route.Example: If a bus travels a distance of 5.25 kilometers from the start
     * of the shape to the stop,shape_dist_traveled=5.25.
     * Non-negative float */
    stop_times_types::shape_dist_traveled_t getShape_dist_traveled() const { return shape_dist_traveled; }

    /* Indicates if arrival and departure times for a stop are strictly adhered to by the vehicle or if they are
    instead approximate and/or interpolated times. This field allows a GTFS producer to provide interpolated stop-times,
    while indicating that the times are approximate. Valid options are:

        0 - Times are considered approximate.
        1 or empty - Times are considered exact.*/
    timepoint_enum getTimepoint() const { return timepoint; }

    friend std::ostream& operator<<(std::ostream& ostr, const StopTime& stop_times)
    {
        ostr << "trip_id: " << stop_times.trip_id;
        if(stop_times.arrival_time.has_value()) ostr << ", arrival_time: " << stop_times.arrival_time.value();
        if(stop_times.departure_time.has_value()) ostr << ", departure_time: " << stop_times.departure_time.value();
        ostr << ", stop_id: " << stop_times.stop_id;
        ostr << ", stop_sequence: " << stop_times.stop_sequence;
        if(stop_times.stop_headsign.has_value()) ostr << ", stop_headsign: " << stop_times.stop_headsign.value();
        ostr << ", pickup_type: " << static_cast<int>(stop_times.pickup_type);
        ostr << ", drop_off_type: " << static_cast<int>(stop_times.drop_off_type);
        ostr << ", continuous_pickup: " << static_cast<int>(stop_times.continuous_pickup);
        ostr << ", continuous_drop_off: " << static_cast<int>(stop_times.continuous_drop_off);
        if(stop_times.shape_dist_traveled.has_value())
            ostr << ", shape_dist_traveled: " << stop_times.shape_dist_traveled.value();
        ostr << ", timepoint: " << static_cast<int>(stop_times.timepoint);
        return ostr;
    }

private:
    /* Identifies a trip. */
    /* ID referencing trips.trip_id */
    stop_times_types::trip_id_t trip_id;
    std::weak_ptr<Trip> trip;
    friend class GTFS;

    /* Arrival time at a specific stop for a specific trip on a route. If there are not separate times for arrival and
    departure at a stop, enter the same value for arrival_time and departure_time. For times occurring after midnight on
    the service day, enter the time as a value greater than 24:00:00 in HH:MM:SS local time for the day on which the
    trip schedule begins.

    Scheduled stops where the vehicle strictly adheres to the specified arrival and departure times are timepoints. If
    this stop is not a timepoint, it is recommended to provide an estimated or interpolated time. If this is not
    available, arrival_time can be left empty. Further, indicate that interpolated times are provided with timepoint=0.
    If interpolated times are indicated with timepoint=0, then time points must be indicated with timepoint=1. Provide
    arrival times for all stops that are time points. An arrival time must be specified for the first and the last stop
    in a trip.*
     * Time *
     * Conditionally required */
    stop_times_types::arrival_time_t arrival_time;

    /* Departure time from a specific stop for a specific trip on a route. For times occurring after midnight on the
     service day, enter the time as a value greater than 24:00:00 in HH:MM:SS local time for the day on which the trip
     schedule begins. If there are not separate times for arrival and departure at a stop, enter the same value for
     arrival_time and departure_time. See the arrival_time description for more details about using timepoints
     correctly.

     The departure_time field should specify time values whenever possible, including non-binding estimated or
     interpolated times between timepoints.*
     * Time *
     * Conditionally required */
    stop_times_types::departure_time_t departure_time;

    /* Identifies the serviced stop. All stops serviced during a trip must have a record in stop_times.txt. Referenced
     * locations must be stops, not stations or station entrances. A stop may be serviced multiple times in the same
     * trip, and multiple trips and routes may service the same stop.
     * ID referencing stops.stop_id */
    stop_times_types::stop_id_t stop_id;
    std::weak_ptr<Stop> stop;
    std::weak_ptr<Stop> getStop() { return stop; }

    /* Order of stops for a particular trip. The values must increase along the trip but do not need to be
     * consecutive.
     * Example: The first location on the trip could have a stop_sequence=1, the second location on the trip
     * could have a stop_sequence=23, the third location could have a stop_sequence=40, and so on. */
    stop_times_types::stop_sequence_t stop_sequence;

    /* Text that appears on signage identifying the trip's destination to riders. This field overrides the default
     trips.trip_headsign when the headsign changes between stops. If the headsign is displayed for an entire trip, use
     trips.trip_headsign instead.

     A stop_headsign value specified for one stop_time does not apply to subsequent stop_times in the same trip. If you
     want to override the trip_headsign for multiple stop_times in the same trip, the stop_headsign value must be
     repeated in each stop_time row.*/
    stop_times_types::stop_headsign_t stop_headsign;

    /* Indicates pickup method. Valid options are:

        0 or empty - Regularly scheduled pickup.
        1 - No pickup available.
        2 - Must phone agency to arrange pickup.
        3 - Must coordinate with driver to arrange pickup.*/
    pickup_type_enum pickup_type = pickup_type_enum::Unset;

    /* Indicates drop off method. Valid options are:

        0 or empty - Regularly scheduled drop off.
        1 - No drop off available.
        2 - Must phone agency to arrange drop off.
        3 - Must coordinate with driver to arrange drop off.*/
    drop_off_type_enum drop_off_type = drop_off_type_enum::Unset;

    /* Indicates whether a rider can board the transit vehicle at any point along the vehicle’s travel path. The path
    is described by shapes.txt, from this stop_time to the next stop_time in the trip’s stop_sequence. Valid options
    are:

        0 - Continuous stopping pickup.
        1 or empty - No continuous stopping pickup.
        2 - Must phone an agency to arrange continuous pickup.
        3 - Must coordinate with a driver to arrange continuous stopping pickup.

    The continuous pickup behavior indicated in stop_times.txt overrides any behavior defined in routes.txt.*/
    continuous_pickup_enum continuous_pickup = continuous_pickup_enum::Unset;

    /* Indicates whether a rider can alight from the transit vehicle at any point along the vehicle’s travel path as
    described by shapes.txt, from this stop_time to the next stop_time in the trip’s stop_sequence.

        0 - Continuous stopping drop off.
        1 or empty - No continuous stopping drop off.
        2 - Must phone an agency to arrange continuous drop off.
        3 - Must coordinate with a driver to arrange continuous stopping drop off.

    The continuous drop-off behavior indicated in stop_times.txt overrides any behavior defined in routes.txt.*/
    continuous_drop_off_enum continuous_drop_off = continuous_drop_off_enum::Unset;

    /* Actual distance traveled along the associated shape, from the first stop to the stop specified in this record.
     * This field specifies how much of the shape to draw between any two stops during a trip. Must be in the same units
     * used in shapes.txt. Values used for shape_dist_traveled must increase along with stop_sequence; they cannot be
     * used to show reverse travel along a route.Example: If a bus travels a distance of 5.25 kilometers from the start
     * of the shape to the stop,shape_dist_traveled=5.25.
     * Non-negative float */
    stop_times_types::shape_dist_traveled_t shape_dist_traveled;

    /* Indicates if arrival and departure times for a stop are strictly adhered to by the vehicle or if they are
    instead approximate and/or interpolated times. This field allows a GTFS producer to provide interpolated stop-times,
    while indicating that the times are approximate. Valid options are:

        0 - Times are considered approximate.
        1 or empty - Times are considered exact.*/
    timepoint_enum timepoint = timepoint_enum::Unset;
};
