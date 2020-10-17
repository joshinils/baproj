#pragma once
#include <string>

class Levels
{
public:
    Levels();
    ~Levels();

private:
    /* Id of the level that can be referenced from stops.txt. */
    int level_id; // Required

    /* Numeric index of the level that indicates relative position of this level in relation to other levels (levels
    with higher indices are assumed to be located above levels with lower indices).

    Ground level should have index 0, with levels above ground indicated by positive indices and levels below ground by negative indices.*/
    /* float */ double level_index; // Required

    /* Optional name of the level (that matches level lettering/numbering used inside the building or the station). Is
     * useful for elevator routing (e.g. “take the elevator to level “Mezzanine” or “Platforms” or “-1”). */
    std::string level_name; // Optional
};
