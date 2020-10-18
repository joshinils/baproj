#pragma once
#include <string>
class Routes
{
public:
    Routes();
    ~Routes();

private:
    /* Identifies a route. */
    int route_id; // Required

    /* Agency for the specified route. This field is required when the dataset provides data for routes from more than
     * one agency in agency.txt, otherwise it is optional. */
    /* ID referencing agency.agency_id */ int agency_id; // Conditionally required

    /* Short name of a route. This will often be a short, abstract identifier like "32", "100X", or "Green" that
     * riders use to identify a route, but which doesn't give any indication of what places the route serves. Either
     * route_short_name or route_long_name must be specified, or potentially both if appropriate. */
    std::string route_short_name; // Conditionally required

    /* Full name of a route. This name is generally more descriptive than the route_short_name and often includes the
     * route's destination or stop. Either route_short_name or route_long_name must be specified, or potentially both if
     * appropriate. */
    std::string route_long_name; // Conditionally required

    /* Description of a route that provides useful, quality information. Do not simply duplicate the name of the
     * route. Example: "A" trains operate between Inwood-207 St, Manhattan and Far Rockaway-Mott Avenue, Queens at all
     * times. Also from about 6AM until about midnight, additional "A" trains operate between Inwood-207 St and Lefferts
     * Boulevard (trains typically alternate between Lefferts Blvd and Far Rockaway). */
    std::string route_desc; // Optional

    /* Indicates the type of transportation used on a route. Valid options are:

        0 - Tram, Streetcar, Light rail. Any light rail or street level system within a metropolitan area.
        1 - Subway, Metro. Any underground rail system within a metropolitan area.
        2 - Rail. Used for intercity or long-distance travel.
        3 - Bus. Used for short- and long-distance bus routes.
        4 - Ferry. Used for short- and long-distance boat service.
        5 - Cable tram. Used for street-level rail cars where the cable runs beneath the vehicle, e.g., cable car in
            San Francisco.
        6 - Aerial lift, suspended cable car (e.g., gondola lift, aerial tramway). Cable transport where cabins, cars,
            gondolas or open chairs are suspended by means of one or more cables.
        7 - Funicular. Any rail system designed for steep inclines.
        11 - Trolleybus. Electric buses that draw power from overhead wires using poles.
        12 - Monorail. Railway in which the track consists of a single rail or a beam.*/
    enum class route_type_enum
    {
        //TODO
    };
    route_type_enum route_type; // Required

    /* URL of a web page about the particular route. Should be different from the agency.agency_url value. */
    std::string route_url; // Optional

    /* Route color designation that matches public facing material. Defaults to white (FFFFFF) when omitted or left
     * empty. The color difference between route_color and route_text_color should provide sufficient contrast when
     * viewed on a black and white screen. */
    /* Color */ int route_color; // Optional

    /* Legible color to use for text drawn against a background of route_color. Defaults to black (000000) when
     * omitted or left empty. The color difference between route_color and route_text_color should provide sufficient
     * contrast when viewed on a black and white screen. */
    /* Color */ int route_text_color; // Optional

    /* Orders the routes in a way which is ideal for presentation to customers. Routes with smaller route_sort_order
     * values should be displayed first. */
    unsigned int route_sort_order; // Optional

    /* Indicates whether a rider can board the transit vehicle anywhere along the vehicle’s travel path. The path is
    described by shapes.txt on every trip of the route. Valid options are:

        0 - Continuous stopping pickup.
        1 or empty - No continuous stopping pickup.
        2 - Must phone an agency to arrange continuous stopping pickup.
        3 - Must coordinate with a driver to arrange continuous stopping pickup.

    The default continuous pickup behavior defined in routes.txt can be overridden in stop_times.txt.*/
    enum class continuous_pickup_enum
    {
        //TODO
    };
    continuous_pickup_enum continuous_pickup; // Optional

    /* Indicates whether a rider can alight from the transit vehicle at any point along the vehicle’s travel path. The
    path is described by shapes.txt on every trip of the route. Valid options are:

        0- Continuous stopping drop-off.
        1 or empty - No continuous stopping drop-off.
        2 - Must phone an agency to arrange continuous stopping drop-off.
        3 - Must coordinate with a driver to arrange continuous stopping drop-off.

    The default continuous drop-off behavior defined in routes.txt can be overridden in stop_times.txt.*/
    enum class continuous_drop_off_enum
    {
        //TODO
    };
    continuous_drop_off_enum continuous_drop_off; // Optional
};
