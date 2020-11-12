#pragma once
#include "agency.h"
#include "calendar.h"
#include "calendarDate.h"
#include "fareAttribute.h"
#include "fareRule.h"
#include "feed_info.h"
#include "frequencies.h"
#include "level.h"
#include "pathway.h"
#include "route.h"
#include "shape.h"
#include "stop.h"
#include "stopTime.h"
#include "transfer.h"
#include "trip.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

// allows differential testing with
// std::map vs std::unordered_map
template<typename T, typename U>
using map_t = std::unordered_map<T, U>;

class GTFS
{
public:
    struct ColumnData
    {
    public:
        bool isOptional = false;
        bool exists     = false;
        int index       = -1;
    };


    GTFS(const std::string& folder);
    ~GTFS();

private:
    // Transit agencies with service represented in this dataset.
    std::vector<Agency> agency;
    void readAgency(const std::string& folder);

    // Stops where vehicles pick up or drop off riders. Also defines stations and station entrances.
    map_t<std::string, std::shared_ptr<Stop>> stops;
    void readStops(const std::string& folder);

    // Transit routes. A route is a group of trips that are displayed to riders as a single service.
    map_t<std::string, std::shared_ptr<Route>> routes;
    void readRoutes(const std::string& folder);

    // Trips for each route. A trip is a sequence of two or more stops that occur during a specific time period.
    map_t<int, std::shared_ptr<Trip>> trips;
    void readTrips(const std::string& folder);

    // Times that a vehicle arrives at and departs from stops for each trip.
    std::vector<std::shared_ptr<StopTime>> stop_times;
    void readStopTimes(const std::string& folder);

    // Conditionally required Service dates specified using a weekly schedule with start and end dates.
    // This file is required unless all dates of service are defined in calendar_dates.
    std::optional<std::vector<Calendar>> calendar;
    void readCalendar(const std::string& folder);

    // Conditionally required Exceptions for the services defined in the calendar.
    // If calendar is omitted, then calendar_dates is required and must contain all dates of service.
    std::optional<std::vector<CalendarDate>> calendar_dates;
    void readCalendarDates(const std::string& folder);

    // Optional Fare information for a transit agency's routes.
    std::optional<std::vector<FareAttribute>> fare_attributes;
    void readFareAttributes(const std::string& folder);

    // Optional Rules to apply fares for itineraries.
    std::optional<std::vector<FareRule>> fare_rules;
    void readFareRules(const std::string& folder);

    // Optional Rules for mapping vehicle travel paths, sometimes referred to as route alignments.
    std::optional<std::vector<Shape>> shapes;
    void readShapes(const std::string& folder);

    // Optional Headway (time between trips) for headway-based service
    // or a compressed representation of fixed-schedule service.
    std::optional<std::vector<Frequencies>> frequencies;
    void readFrequencies(const std::string& folder);

    // Optional Rules for making connections at transfer points between routes.
    std::optional<std::vector<Transfer>> transfers;
    void readTransfers(const std::string& folder);

    // Optional Pathways linking together locations within stations.
    std::optional<std::vector<Pathway>> pathways;
    void readPathways(const std::string& folder);

    // Optional Levels within stations.
    std::optional<std::vector<Level>> levels;
    void readLevels(const std::string& folder);

    // Conditionally required Dataset metadata, including publisher, version, and expiration information.
    std::optional<std::vector<Feed_info>> feed_info;
    void readFeedInfo(const std::string& folder);


    void connectTripsStopTimes();
    void connectTripRoutesToRoutesId();
    void connectStopTimesToTripsAndStops();
    
    void setColsToExist(const CSVReader& csvData, map_t<std::string, ColumnData>& cols);

    const int maxPrint = 10;
};
