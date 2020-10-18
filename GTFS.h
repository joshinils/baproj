#pragma once
#include "agency.h"
#include "calendar.h"
#include "calendar_dates.h"
#include "fare_attributes.h"
#include "fare_rules.h"
#include "feed_info.h"
#include "frequencies.h"
#include "levels.h"
#include "pathways.h"
#include "routes.h"
#include "shapes.h"
#include "stop_times.h"
#include "stops.h"
#include "transfers.h"
#include "trips.h"
#include <optional>
#include <string>
#include <vector>

class GTFS
{
public:
    GTFS(const std::string& folder);
    ~GTFS();

private:
    // Transit agencies with service represented in this dataset.
    std::vector<Agency> agency;

    // Stops where vehicles pick up or drop off riders. Also defines stations and station entrances.
    std::vector<Stops> stops;

    // Transit routes. A route is a group of trips that are displayed to riders as a single service.
    std::vector<Routes> routes;

    // Trips for each route. A trip is a sequence of two or more stops that occur during a specific time period.
    std::vector<Trips> trips;

    // Times that a vehicle arrives at and departs from stops for each trip.
    std::vector<Stop_times> stop_times;

    // Conditionally required Service dates specified using a weekly schedule with start and end dates.
    // This file is required unless all dates of service are defined in calendar_dates.
    std::optional<std::vector<Calendar>> calendar;

    // Conditionally required Exceptions for the services defined in the calendar.
    // If calendar is omitted, then calendar_dates is required and must contain all dates of service.
    std::optional<std::vector<Calendar_dates>> calendar_dates;

    // Optional Fare information for a transit agency's routes.
    std::optional<std::vector<Fare_attributes>> fare_attributes;

    // Optional Rules to apply fares for itineraries.
    std::optional<std::vector<Fare_rules>> fare_rules;

    // Optional Rules for mapping vehicle travel paths, sometimes referred to as route alignments.
    std::optional<std::vector<Shapes>> shapes;

    // Optional Headway (time between trips) for headway-based service 
    // or a compressed representation of fixed-schedule service.
    std::optional<std::vector<Frequencies>> frequencies;

    // Optional Rules for making connections at transfer points between routes.
    std::optional<std::vector<Transfers>> transfers;

    // Optional Pathways linking together locations within stations.
    std::optional<std::vector<Pathways>> pathways;

    // Optional Levels within stations.
    std::optional<std::vector<Levels>> levels;

    // Conditionally required Dataset metadata, including publisher, version, and expiration information.
    std::optional<std::vector<Feed_info>> feed_info;
};
