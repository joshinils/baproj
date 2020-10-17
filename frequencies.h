#pragma once

class Frequencies
{
public:
    Frequencies();
    ~Frequencies();

private:
    /* Identifies a trip to which the specified headway of service applies. */
    /* ID referencing trips.trip_id */ int trip_id; // Required

    /* Time at which the first vehicle departs from the first stop of the trip with the specified headway. */
    /* Time */ int start_time; // Required

    /* Time at which service changes to a different headway (or ceases) at the first stop in the trip. */
    /* Time */ int end_time; // Required

    /* Time, in seconds, between departures from the same stop (headway) for the trip, during the time interval
     * specified by start_time and end_time. Multiple headways for the same trip are allowed, but may not overlap. New
     * headways may start at the exact time the previous headway ends. */
    unsigned int headway_secs; // Required

    /* Indicates the type of service for a trip. See the file description for more information. Valid options are:

        0 or empty - Frequency-based trips.
        1 - Schedule-based trips with the exact same headway throughout the day.
            In this case the end_time value must be greater than the last desired trip start_time but less than the
            last desired trip start_time + headway_secs.*/
    enum class exact_times_enum
    {
        Unset, // this field is optional
        FreqBased     = 0, // or empty - Frequency-based trips.
        ScheduleBased = 1, // Schedule-based trips with the exact same headway throughout the day.
    };
    exact_times_enum exact_times = exact_times_enum::Unset; // Optional
};
