#pragma once
#include <iostream>
#include <optional>
#include <string>
class Routes
{
public:
    enum class route_type_enum
    {
        Tram       = 0,
        Subway     = 1,
        Rail       = 2,
        Bus        = 3,
        Ferry      = 4,
        CableTram  = 5,
        AerialLift = 6,
        Funicular  = 7,
        Trolleybus = 11,
        Monorail   = 12,

        // Extended GTFS Route Types:
        RailwayService                   = 100,
        HighSpeedRailService             = 101, // 	TGV (FR), ICE (DE), Eurostar (GB)
        LongDistanceTrains               = 102, // 	InterCity/EuroCity
        InterRegionalRailService         = 103, // 	InterRegio (DE), Cross County Rail (GB)
        CarTransportRailService          = 104,
        SleeperRailService               = 105, // 	GNER Sleeper (GB)
        RegionalRailService              = 106, // 	TER (FR), Regionalzug (DE)
        TouristRailwayService            = 107, // 	Romney, Hythe & Dymchurch (GB)
        RailShuttle_WithinComplex        = 108, // 	Gatwick Shuttle (GB), Sky Line (DE)
        SuburbanRailway                  = 109, // 	S-Bahn (DE), RER (FR), S-tog (Kopenhagen)
        ReplacementRailService           = 110,
        SpecialRailService               = 111,
        LorryTransportRailService        = 112,
        AllRailServices                  = 113,
        CrossCountryRailService          = 114,
        VehicleTransportRailService      = 115,
        RackandPinionRailway             = 116, // 	Rochers de Naye (CH), Dolderbahn (CH)
        AdditionalRailService            = 117,
        CoachService                     = 200,
        InternationalCoachService        = 201, // 	EuroLine, Touring
        NationalCoachService             = 202, // 	National Express (GB)
        ShuttleCoachService              = 203, // 	Roissy Bus (FR), Reading-Heathrow (GB)
        RegionalCoachService             = 204,
        SpecialCoachService              = 205,
        SightseeingCoachService          = 206,
        TouristCoachService              = 207,
        CommuterCoachService             = 208,
        AllCoachServices                 = 209,
        UrbanRailwayService400           = 400,
        MetroService                     = 401, // 	Métro de Paris
        UndergroundService               = 402, // 	London Underground, U-Bahn
        UrbanRailwayService              = 403,
        AllUrbanRailwayServices          = 404,
        Monorail405                      = 405,
        BusService                       = 700,
        RegionalBusService               = 701, // 	Eastbourne-Maidstone (GB)
        ExpressBusService                = 702, // 	X19 Wokingham-Heathrow (GB)
        StoppingBusService               = 703, // 	38 London: Clapton Pond-Victoria (GB)
        LocalBusService                  = 704,
        NightBusService                  = 705, // 	N prefixed buses in London (GB)
        PostBusService                   = 706, // 	Maidstone P4 (GB)
        SpecialNeedsBus                  = 707,
        MobilityBusService               = 708,
        MobilityBusforRegisteredDisabled = 709,
        SightseeingBus                   = 710,
        ShuttleBus                       = 711, // 	747 Heathrow-Gatwick Airport Service (GB)
        SchoolBus                        = 712,
        SchoolandPublicServiceBus        = 713,
        RailReplacementBusService        = 714,
        DemandandResponseBusService      = 715,
        AllBusServices                   = 716,
        TrolleybusService                = 800,
        TramService                      = 900,
        CityTramService                  = 901,
        LocalTramService                 = 902, // 	Munich (DE), Brussels (BE), Croydon (GB)
        RegionalTramService              = 903,
        SightseeingTramService           = 904, // 	Blackpool Seafront (GB)
        ShuttleTramService               = 905,
        AllTramServices                  = 906,
        WaterTransportService            = 1000,
        AirService                       = 1100,
        FerryService                     = 1200,
        AerialLiftService         = 1300, // 	Telefèric de Montjuïc (ES), Saleve (CH), Roosevelt Island Tramway (US)
        FunicularService          = 1400, // 	Rigiblick (Zürich, CH)
        TaxiService               = 1500,
        CommunalTaxiService       = 1501, // 	Marshrutka (RU), dolmuş (TR)
        WaterTaxiService          = 1502,
        RailTaxiService           = 1503,
        BikeTaxiService           = 1504,
        LicensedTaxiService       = 1505,
        PrivateHireServiceVehicle = 1506,
        AllTaxiServices           = 1507,
        MiscellaneousService      = 1700,
        HorseDrawnCarriage        = 1702,
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

    Routes(std::string route_id,
           std::optional<int> agency_id,
           std::optional<std::string> route_short_name,
           std::optional<std::string> route_long_name,
           std::optional<std::string> route_desc,
           route_type_enum route_type,
           std::optional<std::string> route_url,
           std::optional<std::string> route_color,
           std::optional<std::string> route_text_color,
           std::optional<unsigned int> route_sort_order,
           continuous_pickup_enum continuous_pickup,
           continuous_drop_off_enum continuous_drop_off);
    ~Routes();

    /* Identifies a route. */
    std::string getRoute_id() const { return route_id; }

    /* Agency for the specified route. This field is required when the dataset provides data for routes from more than
     * one agency in agency.txt, otherwise it is optional.
     * ID referencing agency.agency_id
     * Conditionally required */
    std::optional<int> getAgency_id() const { return agency_id; }

    /* Short name of a route. This will often be a short, abstract identifier like "32", "100X", or "Green" that
     * riders use to identify a route, but which doesn't give any indication of what places the route serves. Either
     * route_short_name or route_long_name must be specified, or potentially both if appropriate.
     * Conditionally required */
    std::optional<std::string> getRoute_short_name() const { return route_short_name; }

    /* Full name of a route. This name is generally more descriptive than the route_short_name and often includes the
     * route's destination or stop. Either route_short_name or route_long_name must be specified, or potentially both if
     * appropriate.
     * Conditionally required */
    std::optional<std::string> getRoute_long_name() const { return route_long_name; }

    /* Description of a route that provides useful, quality information. Do not simply duplicate the name of the
     * route. Example: "A" trains operate between Inwood-207 St, Manhattan and Far Rockaway-Mott Avenue, Queens at all
     * times. Also from about 6AM until about midnight, additional "A" trains operate between Inwood-207 St and Lefferts
     * Boulevard (trains typically alternate between Lefferts Blvd and Far Rockaway). */
    std::optional<std::string> getRoute_desc() const { return route_desc; }

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
    route_type_enum getRoute_type() const { return route_type; }

    /* URL of a web page about the particular route. Should be different from the agency.agency_url value. */
    std::optional<std::string> getRoute_url() const { return route_url; }

    /* Route color designation that matches public facing material. Defaults to white (FFFFFF) when omitted or left
     * empty. The color difference between route_color and route_text_color should provide sufficient contrast when
     * viewed on a black and white screen.
     *
     * Color */
    std::optional<std::string> getRoute_color() const { return route_color; }

    /* Legible color to use for text drawn against a background of route_color. Defaults to black (000000) when
     * omitted or left empty. The color difference between route_color and route_text_color should provide sufficient
     * contrast when viewed on a black and white screen.
     *
     * Color */
    std::optional<std::string> getRoute_text_color() const { return route_text_color; }

    /* Orders the routes in a way which is ideal for presentation to customers. Routes with smaller route_sort_order
     * values should be displayed first. */
    std::optional<unsigned int> getRoute_sort_order() const { return route_sort_order; }

    /* Indicates whether a rider can board the transit vehicle anywhere along the vehicle’s travel path. The path is
    described by shapes.txt on every trip of the route. Valid options are:

        0 - Continuous stopping pickup.
        1 or empty - No continuous stopping pickup.
        2 - Must phone an agency to arrange continuous stopping pickup.
        3 - Must coordinate with a driver to arrange continuous stopping pickup.

    The default continuous pickup behavior defined in routes.txt can be overridden in stop_times.txt.*/
    continuous_pickup_enum getContinuous_pickup() const { return continuous_pickup; }

    /* Indicates whether a rider can alight from the transit vehicle at any point along the vehicle’s travel path. The
    path is described by shapes.txt on every trip of the route. Valid options are:

        0 - Continuous stopping drop-off.
        1 or empty - No continuous stopping drop-off.
        2 - Must phone an agency to arrange continuous stopping drop-off.
        3 - Must coordinate with a driver to arrange continuous stopping drop-off.

    The default continuous drop-off behavior defined in routes.txt can be overridden in stop_times.txt.*/
    continuous_drop_off_enum getContinuous_drop_off() const { return continuous_drop_off; }

    friend std::ostream& operator<<(std::ostream& ostr, const Routes& routes)
    {
        ostr << "route_id: " << routes.route_id;
        if(routes.agency_id.has_value()) ostr << ", agency_id: " << routes.agency_id.value();
        if(routes.route_short_name.has_value()) ostr << ", route_short_name: " << routes.route_short_name.value();
        if(routes.route_long_name.has_value()) ostr << ", route_long_name: " << routes.route_long_name.value();
        if(routes.route_desc.has_value()) ostr << ", route_desc: " << routes.route_desc.value();
        ostr << ", route_type: " << static_cast<int>(routes.route_type);
        if(routes.route_url.has_value()) ostr << ", route_url: " << routes.route_url.value();
        if(routes.route_color.has_value()) ostr << ", route_color: " << routes.route_color.value();
        if(routes.route_text_color.has_value()) ostr << ", route_text_color: " << routes.route_text_color.value();
        if(routes.route_sort_order.has_value()) ostr << ", route_sort_order: " << routes.route_sort_order.value();
        ostr << ", continuous_pickup: " << static_cast<int>(routes.continuous_pickup);
        ostr << ", continuous_drop_off: " << static_cast<int>(routes.continuous_drop_off);
        return ostr;
    }

private:
    /* Identifies a route. */
    std::string route_id;

    /* Agency for the specified route. This field is required when the dataset provides data for routes from more than
     * one agency in agency.txt, otherwise it is optional.
     * ID referencing agency.agency_id
     * Conditionally required */
    std::optional<int> agency_id;

    /* Short name of a route. This will often be a short, abstract identifier like "32", "100X", or "Green" that
     * riders use to identify a route, but which doesn't give any indication of what places the route serves. Either
     * route_short_name or route_long_name must be specified, or potentially both if appropriate.
     * Conditionally required */
    std::optional<std::string> route_short_name;

    /* Full name of a route. This name is generally more descriptive than the route_short_name and often includes the
     * route's destination or stop. Either route_short_name or route_long_name must be specified, or potentially both if
     * appropriate.
     * Conditionally required */
    std::optional<std::string> route_long_name;

    /* Description of a route that provides useful, quality information. Do not simply duplicate the name of the
     * route. Example: "A" trains operate between Inwood-207 St, Manhattan and Far Rockaway-Mott Avenue, Queens at all
     * times. Also from about 6AM until about midnight, additional "A" trains operate between Inwood-207 St and Lefferts
     * Boulevard (trains typically alternate between Lefferts Blvd and Far Rockaway). */
    std::optional<std::string> route_desc;

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
    route_type_enum route_type;

    /* URL of a web page about the particular route. Should be different from the agency.agency_url value. */
    std::optional<std::string> route_url;

    /* Route color designation that matches public facing material. Defaults to white (FFFFFF) when omitted or left
     * empty. The color difference between route_color and route_text_color should provide sufficient contrast when
     * viewed on a black and white screen.
     *
     * Color */
    std::optional<std::string> route_color;

    /* Legible color to use for text drawn against a background of route_color. Defaults to black (000000) when
     * omitted or left empty. The color difference between route_color and route_text_color should provide sufficient
     * contrast when viewed on a black and white screen.
     *
     * Color */
    std::optional<std::string> route_text_color;

    /* Orders the routes in a way which is ideal for presentation to customers. Routes with smaller route_sort_order
     * values should be displayed first. */
    std::optional<unsigned int> route_sort_order;

    /* Indicates whether a rider can board the transit vehicle anywhere along the vehicle’s travel path. The path is
    described by shapes.txt on every trip of the route. Valid options are:

        0 - Continuous stopping pickup.
        1 or empty - No continuous stopping pickup.
        2 - Must phone an agency to arrange continuous stopping pickup.
        3 - Must coordinate with a driver to arrange continuous stopping pickup.

    The default continuous pickup behavior defined in routes.txt can be overridden in stop_times.txt.*/
    continuous_pickup_enum continuous_pickup = continuous_pickup_enum::Unset;

    /* Indicates whether a rider can alight from the transit vehicle at any point along the vehicle’s travel path. The
    path is described by shapes.txt on every trip of the route. Valid options are:

        0 - Continuous stopping drop-off.
        1 or empty - No continuous stopping drop-off.
        2 - Must phone an agency to arrange continuous stopping drop-off.
        3 - Must coordinate with a driver to arrange continuous stopping drop-off.

    The default continuous drop-off behavior defined in routes.txt can be overridden in stop_times.txt.*/
    continuous_drop_off_enum continuous_drop_off = continuous_drop_off_enum::Unset;
};
