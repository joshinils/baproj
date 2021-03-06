#pragma once
#include "type_aliases.h"
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

class StopTime;
class GTFS;

class Stop
{
public:
    enum class location_type_enum
    {
        Unset        = -1, /// this field is optional
        Stop         = 0, //(or empty): A location where passengers board or disembark from a transit vehicle.
        Station      = 1, /// A physical structure or area that contains one or more platform.
        EntranceExit = 2, /// A location where passengers can enter or exit a station from the street.
        GenericNode  = 3, /// A location within a station, not matching any other location_type
        BoardingArea = 4, /// A specific location on a platform, where passengers can board and/or alight vehicles.
    };

    enum class wheelchair_boarding_enum
    {
        Unset                  = -1, /// this field is optional
        NoInfo_orInherited     = 0, /// Stop will inherit its wheelchair_boarding behavior from the parent station
        WheelchairAccessible   = 1, /// Stop is wheelchair accessible.
        WheelchairInAccessible = 2, /// Wheelchair boarding is not possible at this stop.
    };

    Stop(stop_types::stop_id_t stop_id,
         stop_types::stop_code_t stop_code,
         stop_types::stop_name_t stop_name,
         stop_types::stop_desc_t stop_desc,
         stop_types::stop_lat_t stop_lat,
         stop_types::stop_lon_t stop_lon,
         stop_types::zone_id_t zone_id,
         stop_types::stop_url_t stop_url,
         location_type_enum location_type,
         stop_types::parent_station_t parent_station,
         stop_types::stop_timezone_t stop_timezone,
         wheelchair_boarding_enum wheelchair_boarding,
         stop_types::level_id_t level_id,
         stop_types::platform_code_t platform_code);
    ~Stop();

    /** Identifies a stop, station, or station entrance.

    The term ""station entrance"" refers to both station entrances and station exits. Stops,
    stations or station entrances are collectively referred to as locations. Multiple routes may use the same stop.*/
    stop_types::stop_id_t getStop_id() const { return stop_id; }

    /** Short text or a number that identifies the location for riders. These codes are often used in phone-based
     * transit information systems or printed on signage to make it easier for riders to get information for a
     * particular location. The stop_code can be the same as stop_id if it is public facing. This field should be left
     * empty for locations without a code presented to riders. */
    stop_types::stop_code_t getStop_code() const { return stop_code; }

    /** Name of the location. Use a name that people will understand in the local and tourist vernacular.

    When the location is a boarding area (location_type=4), the stop_name should contains the name of the boarding area
    as displayed by the agency. It could be just one letter (like on some European intercity railway stations), or text
    like “Wheelchair boarding area” (NYC’s Subway) or “Head of short trains” (Paris’ RER).

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Conditionally Required */
    stop_types::stop_name_t getStop_name() const { return stop_name; }

    /** Description of the location that provides useful, quality information. Do not simply duplicate the name of the
     * location. */
    stop_types::stop_desc_t getStop_desc() const { return stop_desc; }

    /** Latitude of the location.

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Latitude
    Conditionally Required */
    stop_types::stop_lat_t getStop_lat() const { return stop_lat; }

    /** Longitude of the location.

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Longitude
    Conditionally Required */
    stop_types::stop_lon_t getStop_lon() const { return stop_lon; }

    /** Identifies the fare zone for a stop. This field is required if providing fare information using fare_rules.txt,
     * otherwise it is optional. If this record represents a station or station entrance, the zone_id is ignored.
     * Conditionally Required */
    stop_types::zone_id_t getZone_id() const { return zone_id; }

    /** URL of a web page about the location. This should be different from the agency.agency_url and the
     * routes.route_url field values. */
    stop_types::stop_url_t getStop_url() const { return stop_url; }


    /** Type of the location:
        • 0 (or empty): Stop (or Platform). A location where passengers board or disembark from a transit vehicle.
            Is called a platform when defined within a parent_station.
        • 1: Station. A physical structure or area that contains one or more platform.
        • 2: Entrance/Exit. A location where passengers can enter or exit a station from the street.
            If an entrance/exit belongs to multiple stations, it can be linked by pathways to both,
            but the data provider must pick one of them as parent.
        • 3: Generic Node. A location within a station, not matching any other location_type,
            which can be used to link together pathways define in pathways.txt.
        • 4: Boarding Area. A specific location on a platform, where passengers can board and/or alight vehicles.*/
    location_type_enum getLocation_type() const { return location_type; }

    /** Defines hierarchy between the different locations defined in stops.txt. It contains the ID of the parent
    location, as followed:
        • Stop/platform (location_type=0): the parent_station field contains the ID of a station.
        • Station (location_type=1): this field must be empty.
        • Entrance/exit (location_type=2) or generic node (location_type=3):
            the parent_station field contains the ID of a station (location_type=1)
        • Boarding Area (location_type=4): the parent_station field contains ID of a platform.

    Conditionally Required:
        • Required for locations which are entrances (location_type=2), generic nodes (location_type=3)
            or boarding areas (location_type=4).
        • Optional for stops/platforms (location_type=0).
        • Forbidden for stations (location_type=1).

    ID referencing stops.stop_id
    Conditionally Required */
    stop_types::parent_station_t getParent_station() const { return parent_station; }

    /** Timezone of the location. If the location has a parent station, it inherits the parent station’s timezone
     * instead of applying its own. Stations and parentless stops with empty stop_timezone inherit the timezone
     * specified by agency.agency_timezone. If stop_timezone values are provided, the times in stop_times.txt should be
     * entered as the time since midnight in the timezone specified by agency.agency_timezone. This ensures that the
     * time values in a trip always increase over the course of a trip, regardless of which timezones the trip crosses.
     */
    stop_types::stop_timezone_t getStop_timezone() const { return stop_timezone; }

    /** Indicates whether wheelchair boardings are possible from the location. Valid options are:

    For parentless stops:
        0 or empty - No accessibility information for the stop.
        1 - Some vehicles at this stop can be boarded by a rider in a wheelchair.
        2 - Wheelchair boarding is not possible at this stop.

    For child stops:
        0 or empty - Stop will inherit its wheelchair_boarding behavior from the parent station,
            if specified in the parent.
        1 - There exists some accessible path from outside the station to the specific stop/platform.
        2 - There exists no accessible path from outside the station to the specific stop/platform.

    For station entrances/exits:
        0 or empty - Station entrance will inherit its wheelchair_boarding behavior from the parent station,
            if specified for the parent.
        1 - Station entrance is wheelchair accessible.
        2 - No accessible path from station entrance to stops/platforms.*/
    wheelchair_boarding_enum getWheelchair_boarding() const { return wheelchair_boarding; }

    /** Level of the location. The same level can be used by multiple unlinked stations.
     * ID referencing levels.level_id */
    stop_types::level_id_t getLevel_id() const { return level_id; }

    /** Platform identifier for a platform stop (a stop belonging to a station). This should be just the platform
     * identifier (eg. "G" or "3"). Words like “platform” or "track" (or the feed’s language-specific equivalent) should
     * not be included. This allows feed consumers to more easily internationalize and localize the platform identifier
     * into other languages. */
    stop_types::platform_code_t getPlatform_code() const { return platform_code; }

    friend std::ostream& operator<<(std::ostream& ostr, const Stop& stops)
    {
        ostr << "stop_id: " << stops.stop_id;
        if(stops.stop_code.has_value()) ostr << ", stop_code: " << stops.stop_code.value();
        if(stops.stop_name.has_value()) ostr << ", stop_name: " << stops.stop_name.value();
        if(stops.stop_desc.has_value()) ostr << ", stop_desc: " << stops.stop_desc.value();
        if(stops.stop_lat.has_value()) ostr << ", stop_lat: " << stops.stop_lat.value();
        if(stops.stop_lon.has_value()) ostr << ", stop_lon: " << stops.stop_lon.value();
        if(stops.zone_id.has_value()) ostr << ", zone_id: " << stops.zone_id.value();
        if(stops.stop_url.has_value()) ostr << ", stop_url: " << stops.stop_url.value();
        ostr << ", location_type: " << static_cast<int>(stops.location_type);
        if(stops.parent_station.has_value()) ostr << ", parent_station: " << stops.parent_station.value();
        if(stops.stop_timezone.has_value()) ostr << ", stop_timezone: " << stops.stop_timezone.value();
        ostr << ", wheelchair_boarding: " << static_cast<int>(stops.wheelchair_boarding);
        if(stops.level_id.has_value()) ostr << ", level_id: " << stops.level_id.value();
        if(stops.platform_code.has_value()) ostr << ", platform_code: " << stops.platform_code.value();

        return ostr;
    }

private:
    /** Identifies a stop, station, or station entrance.

    The term ""station entrance"" refers to both station entrances and station exits. Stops,
    stations or station entrances are collectively referred to as locations. Multiple routes may use the same stop.*/
    stop_types::stop_id_t stop_id;

    /** Short text or a number that identifies the location for riders. These codes are often used in phone-based
     * transit information systems or printed on signage to make it easier for riders to get information for a
     * particular location. The stop_code can be the same as stop_id if it is public facing. This field should be left
     * empty for locations without a code presented to riders. */
    stop_types::stop_code_t stop_code;

    /** Name of the location. Use a name that people will understand in the local and tourist vernacular.

    When the location is a boarding area (location_type=4), the stop_name should contains the name of the boarding area
    as displayed by the agency. It could be just one letter (like on some European intercity railway stations), or text
    like “Wheelchair boarding area” (NYC’s Subway) or “Head of short trains” (Paris’ RER).

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Conditionally Required */
    stop_types::stop_name_t stop_name;

    /** Description of the location that provides useful, quality information. Do not simply duplicate the name of the
     * location. */
    stop_types::stop_desc_t stop_desc;

    /** Latitude of the location.

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Latitude
    Conditionally Required */
    stop_types::stop_lat_t stop_lat;

    /** Longitude of the location.

    Conditionally Required:
        • Required for locations which are stops (location_type=0), stations (location_type=1)
            or entrances/exits (location_type=2).
        • Optional for locations which are generic nodes (location_type=3) or boarding areas (location_type=4).
    Longitude
    Conditionally Required */
    stop_types::stop_lon_t stop_lon;

    /** Identifies the fare zone for a stop. This field is required if providing fare information using fare_rules.txt,
     * otherwise it is optional. If this record represents a station or station entrance, the zone_id is ignored.
     * Conditionally Required */
    stop_types::zone_id_t zone_id;

    /** URL of a web page about the location. This should be different from the agency.agency_url and the
     * routes.route_url field values. */
    stop_types::stop_url_t stop_url;

    /** Type of the location:
        • 0 (or empty): Stop (or Platform). A location where passengers board or disembark from a transit vehicle.
            Is called a platform when defined within a parent_station.
        • 1: Station. A physical structure or area that contains one or more platform.
        • 2: Entrance/Exit. A location where passengers can enter or exit a station from the street.
            If an entrance/exit belongs to multiple stations, it can be linked by pathways to both,
            but the data provider must pick one of them as parent.
        • 3: Generic Node. A location within a station, not matching any other location_type,
            which can be used to link together pathways define in pathways.txt.
        • 4: Boarding Area. A specific location on a platform, where passengers can board and/or alight vehicles.*/
    location_type_enum location_type = location_type_enum::Unset;

    /** Defines hierarchy between the different locations defined in stops.txt. It contains the ID of the parent
    location, as followed:
        • Stop/platform (location_type=0): the parent_station field contains the ID of a station.
        • Station (location_type=1): this field must be empty.
        • Entrance/exit (location_type=2) or generic node (location_type=3):
            the parent_station field contains the ID of a station (location_type=1)
        • Boarding Area (location_type=4): the parent_station field contains ID of a platform.

    Conditionally Required:
        • Required for locations which are entrances (location_type=2), generic nodes (location_type=3)
            or boarding areas (location_type=4).
        • Optional for stops/platforms (location_type=0).
        • Forbidden for stations (location_type=1).

    ID referencing stops.stop_id
    Conditionally Required */
    stop_types::parent_station_t parent_station;

    /** Timezone of the location. If the location has a parent station, it inherits the parent station’s timezone
     * instead of applying its own. Stations and parentless stops with empty stop_timezone inherit the timezone
     * specified by agency.agency_timezone. If stop_timezone values are provided, the times in stop_times.txt should be
     * entered as the time since midnight in the timezone specified by agency.agency_timezone. This ensures that the
     * time values in a trip always increase over the course of a trip, regardless of which timezones the trip crosses.
     */
    stop_types::stop_timezone_t stop_timezone;

    /** Indicates whether wheelchair boardings are possible from the location. Valid options are:

    For parentless stops:
        0 or empty - No accessibility information for the stop.
        1 - Some vehicles at this stop can be boarded by a rider in a wheelchair.
        2 - Wheelchair boarding is not possible at this stop.

    For child stops:
        0 or empty - Stop will inherit its wheelchair_boarding behavior from the parent station,
            if specified in the parent.
        1 - There exists some accessible path from outside the station to the specific stop/platform.
        2 - There exists no accessible path from outside the station to the specific stop/platform.

    For station entrances/exits:
        0 or empty - Station entrance will inherit its wheelchair_boarding behavior from the parent station,
            if specified for the parent.
        1 - Station entrance is wheelchair accessible.
        2 - No accessible path from station entrance to stops/platforms.*/
    wheelchair_boarding_enum wheelchair_boarding = wheelchair_boarding_enum::Unset;

    /** Level of the location. The same level can be used by multiple unlinked stations. */
    /** ID referencing levels.level_id */
    stop_types::level_id_t level_id;

    /** Platform identifier for a platform stop (a stop belonging to a station). This should be just the platform
     * identifier (eg. "G" or "3"). Words like “platform” or "track" (or the feed’s language-specific equivalent) should
     * not be included. This allows feed consumers to more easily internationalize and localize the platform identifier
     * into other languages. */
    stop_types::platform_code_t platform_code;


    /***
     * additional data not from read files
     * ***/

    friend GTFS;
    /// store the stop_time instances which reference this trip
    std::map<stop_times_types::arrival_time_t, std::weak_ptr<StopTime>> includedStopTimes;
};
