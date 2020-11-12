#pragma once

class Transfer
{
public:
    Transfer();
    ~Transfer();

private:
    /* Identifies a stop or station where a connection between routes begins. If this field refers to a station, the
     * transfer rule applies to all its child stops. */
    /* ID referencing stops.stop_id */ int from_stop_id; // Required

    /* Identifies a stop or station where a connection between routes ends. If this field refers to a station, the
     * transfer rule applies to all child stops. */
    /* ID referencing stops.stop_id */ int to_stop_id; // Required

    /* Indicates the type of connection for the specified (from_stop_id, to_stop_id) pair. Valid options are:

        0 or empty - Recommended transfer point between routes.
        1 - Timed transfer point between two routes. The departing vehicle is expected to wait for the arriving one and
            leave sufficient time for a rider to transfer between routes.
        2 - Transfer requires a minimum amount of time between arrival and departure to ensure a connection. The time
            required to transfer is specified by min_transfer_time.
        3 - Transfers are not possible between routes at the location.*/
    enum class transfer_type_enum
    {
        Recommended     = 0, // or empty - Recommended transfer point between routes.
        TimedWait       = 1, // Timed transfer point between two routes. The departing vehicle is expected to wait
        MinTransferTime = 2, // Transfer requires a minimum amount of time between arrival and departure
        Impossible      = 3, // Transfers are not possible between routes at the location.
    };
    transfer_type_enum transfer_type; // Required

    /* Amount of time, in seconds, that must be available to permit a transfer between routes at the specified stops.
     * The min_transfer_time should be sufficient to permit a typical rider to move between the two stops, including
     * buffer time to allow for schedule variance on each route. */
    unsigned int min_transfer_time; // Optional
};
