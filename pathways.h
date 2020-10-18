#pragma once
#include <string>
class Pathways
{
public:
    Pathways();
    ~Pathways();

private:
    /* The pathway_id field contains an ID that uniquely identifies the pathway. The pathway_id is used by systems as
     an internal identifier of this record (e.g., primary key in database), and therefore the pathway_id must be dataset
     unique.
     Different pathways can go from the same from_stop_id to the same to_stop_id. For example, this happens when two
     escalators are side by side in opposite direction, or when a stair is nearby and elevator and both go from the
     same place to the same place.*/
    int pathway_id; // Required

    /* Location at which the pathway begins. It contains a stop_id that identifies a platform, entrance/exit, generic
     * node or boarding area from the stops.txt file. */
    /* ID referencing stops.stop_id */ int from_stop_id; // Required

    /* Location at which the pathway ends. It contains a stop_id that identifies a platform, entrance/exit, generic
     * node or boarding area from the stops.txt file. */
    /* ID referencing stops.stop_id */ int to_stop_id; // Required

    /* Type of pathway between the specified (from_stop_id, to_stop_id) pair. Valid values for this field are:
        • 1: walkway
        • 2: stairs
        • 3: moving sidewalk/travelator
        • 4: escalator
        • 5: elevator
        • 6: fare gate (or payment gate): A pathway that crosses into an area of the station where a proof of payment is
            required (usually via a physical payment gate).
            Fare gates may either separate paid areas of the station from unpaid ones, or separate different payment
            areas within the same station from each other. This information can be used to avoid routing passengers
            through stations using shortcuts that would require passengers to make unnecessary payments, like directing
            a passenger to walk through a subway platform to reach a busway.
        • 7: exit gate: Indicates a pathway exiting an area where proof-of-payment is required into an area where
            proof-of-payment is no longer required.*/
    enum class pathway_mode_enum
    {
        Walkway        = 1,
        Stairs         = 2,
        movingSidewalk = 3,
        Escalator      = 4,
        Elevator       = 5,
        FareGate       = 6,
        ExitGate       = 7,
    };
    pathway_mode_enum pathway_mode; // Required

    /* Indicates in which direction the pathway can be used:
        • 0 (false): Unidirectional pathway, it can only be used from from_stop_id to to_stop_id.
        • 1 (true): Bidirectional pathway, it can be used in the two directions.

    Fare gates (pathway_mode=6) and exit gates (pathway_mode=7) cannot be bidirectional.*/
    bool is_bidirectional; // Required

    /* Horizontal length in meters of the pathway from the origin location (defined in from_stop_id) to the
    destination location (defined in to_stop_id).

    This field is recommended for walkways (pathway_mode=1), fare gates (pathway_mode=6)
    and exit gates (pathway_mode=7).*/
    /* Non-negative float */ double length; // Optional

    /* Average time in seconds needed to walk through the pathway from the origin location (defined in from_stop_id)
    to the destination location (defined in to_stop_id).

    This field is recommended for moving sidewalks (pathway_mode=3), escalators (pathway_mode=4)
    and elevator (pathway_mode=5).*/
    unsigned int traversal_time; // Optional

    /* Number of stairs of the pathway.

    Best Practices: one could use the approximation of 1 floor = 15 stairs to generate approximative values.

    A positive stair_count implies that the rider walk up from from_stop_id to to_stop_id.
    And a negative stair_count implies that the rider walk down from from_stop_id to to_stop_id.

    This field is recommended for stairs (pathway_mode=2).*/
    /* Non-null Integer */ int stair_count; // Optional

    /* Maximum slope ratio of the pathway. Valid values for this field are:
        • 0 or (empty): no slope.
        • A float: slope ratio of the pathway, positive for upwards, negative for downwards.

    This field should be used only with walkways (pathway_type=1) and moving sidewalks (pathway_type=3).

    Example: In the US, 0.083 (also written 8.3%) is the maximum slope ratio for hand-propelled wheelchair,
    which mean an increase of 0.083m (so 8.3cm) for each 1m.*/
    /* float */ double max_slope; // Optional

    /* Minimum width of the pathway in meters.

    This field is highly recommended if the minimum width is less than 1 meter.*/
    /* Positive float */ double min_width; // Optional

    /* String of text from physical signage visible to transit riders. The string can be used to provide text
     * directions to users, such as 'follow signs to '. The language text should appear in this field exactly how it is
     * printed on the signs - it should not be translated. */
    std::string signposted_as; // Optional

    /* Same than the signposted_as field, but when the pathways is used backward, i.e. from the to_stop_id to the
     * from_stop_id. */
    std::string reversed_signposted_as; // Optional
};
