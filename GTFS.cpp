#include "GTFS.h"
#include "CSVReader.h"
#include <exception>
#include <filesystem>
#include <map>
#include <unordered_map>

template<typename T>
T makeValue(const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists) { return T(row[cd.index]); }
    else if(cd.isOptional)
    {
        return T();
    }
    else
    {
        throw std::domain_error("required field \"" + name + "\" does not exist!");
    }
}

template<>
std::optional<int> makeValue<std::optional<int>>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                 const std::string& name,
                                                 const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists)
        if(row[cd.index].empty()) return std::optional<int>();
        else
            return std::stoi(row[cd.index]);
    else if(cd.isOptional)
        return std::optional<int>();
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
std::optional<unsigned int> makeValue<std::optional<unsigned int>>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                                   const std::string& name,
                                                                   const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists)
        if(row[cd.index].empty()) return std::optional<unsigned int>();
        else
            return std::stoi(row[cd.index]);
    else if(cd.isOptional)
        return std::optional<unsigned int>();
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
std::optional<long long> makeValue<std::optional<long long>>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                             const std::string& name,
                                                             const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists)
        if(row[cd.index].empty()) return std::optional<long long>();
        else
            return std::stoll(row[cd.index]);
    else if(cd.isOptional)
        return std::optional<long long>();
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
int makeValue<int>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                   const std::string& name,
                   const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists)
        if(row[cd.index].empty()) return int();
        else
            return std::stoi(row[cd.index]);
    else if(cd.isOptional)
        return int();
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
unsigned int makeValue<unsigned int>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                     const std::string& name,
                                     const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists && !row[cd.index].empty() && !cd.isOptional) return std::stoul(row[cd.index]);
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
Stop::location_type_enum makeValue<Stop::location_type_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                             const std::string& name,
                                                             const CSVReader::Row& row)
{
    return Stop::location_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop::wheelchair_boarding_enum makeValue<Stop::wheelchair_boarding_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stop::wheelchair_boarding_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Route::route_type_enum makeValue<Route::route_type_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                         const std::string& name,
                                                         const CSVReader::Row& row)
{
    auto rv = makeValue<std::optional<int>>(cdMap, name, row);
    if(rv.has_value()) return Route::route_type_enum(rv.value());
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
Route::continuous_pickup_enum makeValue<Route::continuous_pickup_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Route::continuous_pickup_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Route::continuous_drop_off_enum makeValue<Route::continuous_drop_off_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Route::continuous_drop_off_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trip::direction_id_enum makeValue<Trip::direction_id_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                           const std::string& name,
                                                           const CSVReader::Row& row)
{
    return Trip::direction_id_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trip::wheelchair_accessible_enum makeValue<Trip::wheelchair_accessible_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Trip::wheelchair_accessible_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trip::bikes_allowed_enum makeValue<Trip::bikes_allowed_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                             const std::string& name,
                                                             const CSVReader::Row& row)
{
    return Trip::bikes_allowed_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
StopTime::pickup_type_enum makeValue<StopTime::pickup_type_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                                 const std::string& name,
                                                                 const CSVReader::Row& row)
{
    return StopTime::pickup_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
StopTime::drop_off_type_enum makeValue<StopTime::drop_off_type_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                                     const std::string& name,
                                                                     const CSVReader::Row& row)
{
    return StopTime::drop_off_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
StopTime::continuous_pickup_enum makeValue<StopTime::continuous_pickup_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return StopTime::continuous_pickup_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
StopTime::continuous_drop_off_enum makeValue<StopTime::continuous_drop_off_enum>(
const map_t<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return StopTime::continuous_drop_off_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
StopTime::timepoint_enum makeValue<StopTime::timepoint_enum>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                             const std::string& name,
                                                             const CSVReader::Row& row)
{
    return StopTime::timepoint_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
std::optional<double> makeValue<std::optional<double>>(const map_t<std::string, GTFS::ColumnData>& cdMap,
                                                       const std::string& name,
                                                       const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists)
        if(row[cd.index].empty()) return std::optional<double>();
        else
            return std::stod(row[cd.index]);
    else if(cd.isOptional)
        return std::optional<double>();
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

void GTFS::setColsToExist(const CSVReader& csvData, map_t<std::string, ColumnData>& cols)
{
    int colIndex = 0;
    for(const auto& colName : csvData.getHeader())
    {
        cols[colName].exists = true;
        cols[colName].index  = colIndex;
        ++colIndex;
    }
}

void GTFS::readAgency(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/agency.txt")) throw std::string(folder + "/agency.txt not found!");

    CSVReader csvData(folder + "/agency.txt");
    csvData.printCSV();

    map_t<std::string, ColumnData> cols;

    cols.emplace("agency_id", ColumnData{});
    cols.emplace("agency_name", ColumnData{});
    cols.emplace("agency_url", ColumnData{});
    cols.emplace("agency_timezone", ColumnData{});
    cols.emplace("agency_lang", ColumnData{});
    cols.emplace("agency_phone", ColumnData{});
    cols.emplace("agency_fare_url", ColumnData{});
    cols.emplace("agency_email", ColumnData{});

    cols["agency_id"].isOptional       = true;
    cols["agency_name"].isOptional     = false;
    cols["agency_url"].isOptional      = false;
    cols["agency_timezone"].isOptional = false;
    cols["agency_lang"].isOptional     = true;
    cols["agency_phone"].isOptional    = true;
    cols["agency_fare_url"].isOptional = true;
    cols["agency_email"].isOptional    = true;

    setColsToExist(csvData, cols);

    for(auto const& row : csvData)
    {
        this->agency.emplace_back(Agency(makeValue<std::optional<int>>(cols, "agency_id", row),
                                         makeValue<std::string>(cols, "agency_name", row),
                                         makeValue<std::string>(cols, "agency_url", row),
                                         makeValue<std::string>(cols, "agency_timezone", row),
                                         makeValue<std::optional<std::string>>(cols, "agency_lang", row),
                                         makeValue<std::optional<std::string>>(cols, "agency_phone", row),
                                         makeValue<std::optional<std::string>>(cols, "agency_fare_url", row),
                                         makeValue<std::optional<std::string>>(cols, "agency_email", row)));
    }
    for(size_t i = 0; i < this->agency.size() && i < this->maxPrint; i++) { std::cout << this->agency[i] << std::endl; }
}


void GTFS::readStops(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/stops.txt")) throw std::string(folder + "/stops.txt not found!");

    CSVReader csvData(folder + "/stops.txt");
    csvData.printCSV();

    map_t<std::string, ColumnData> cols;

    cols.emplace("stop_id", ColumnData{});
    cols.emplace("stop_code", ColumnData{});
    cols.emplace("stop_name", ColumnData{});
    cols.emplace("stop_desc", ColumnData{});
    cols.emplace("stop_lat", ColumnData{});
    cols.emplace("stop_lon", ColumnData{});
    cols.emplace("zone_id", ColumnData{});
    cols.emplace("stop_url", ColumnData{});
    cols.emplace("location_type", ColumnData{});
    cols.emplace("parent_station", ColumnData{});
    cols.emplace("stop_timezone", ColumnData{});
    cols.emplace("wheelchair_boarding", ColumnData{});
    cols.emplace("level_id", ColumnData{});
    cols.emplace("platform_code", ColumnData{});

    cols["stop_id"].isOptional             = false;
    cols["stop_code"].isOptional           = true;
    cols["stop_name"].isOptional           = true;
    cols["stop_desc"].isOptional           = true;
    cols["stop_lat"].isOptional            = true;
    cols["stop_lon"].isOptional            = true;
    cols["zone_id"].isOptional             = true;
    cols["stop_url"].isOptional            = true;
    cols["location_type"].isOptional       = true;
    cols["parent_station"].isOptional      = true;
    cols["stop_timezone"].isOptional       = true;
    cols["wheelchair_boarding"].isOptional = true;
    cols["level_id"].isOptional            = true;
    cols["platform_code"].isOptional       = true;

    setColsToExist(csvData, cols);

    std::string stop_id;
    for(auto const& row : csvData)
    {
        stop_id = makeValue<std::string>(cols, "stop_id", row);
        if(this->stops.count(stop_id) > 0)
            throw std::domain_error(std::string("duplicate stop_id \"") + stop_id + "\" found in \"" + folder
                                    + "/stops.txt\"");
        this->stops.emplace(
        stop_id,
        std::make_shared<Stop>(Stop(stop_id,
                                    makeValue<std::optional<std::string>>(cols, "stop_code", row),
                                    makeValue<std::optional<std::string>>(cols, "stop_name", row),
                                    makeValue<std::optional<std::string>>(cols, "stop_desc", row),
                                    makeValue<std::optional<double>>(cols, "stop_lat", row),
                                    makeValue<std::optional<double>>(cols, "stop_lon", row),
                                    makeValue<std::optional<std::string>>(cols, "zone_id", row),
                                    makeValue<std::optional<std::string>>(cols, "stop_url", row),
                                    makeValue<Stop::location_type_enum>(cols, "location_type", row),
                                    makeValue<std::optional<long long>>(cols, "parent_station", row),
                                    makeValue<std::optional<std::string>>(cols, "stop_timezone", row),
                                    makeValue<Stop::wheelchair_boarding_enum>(cols, "wheelchair_boarding", row),
                                    makeValue<std::optional<int>>(cols, "level_id", row),
                                    makeValue<std::optional<std::string>>(cols, "platform_code", row))));
    }
    int i = 0;
    for(const auto& stop : this->stops)
    {
        std::cout << *(stop.second) << std::endl;
        if(++i > this->maxPrint) break;
    }
}

void GTFS::readRoutes(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/routes.txt")) throw std::string(folder + "/routes.txt not found!");

    CSVReader csvData(folder + "/routes.txt");
    csvData.printCSV();

    map_t<std::string, ColumnData> cols;

    cols.emplace("route_id", ColumnData{});
    cols.emplace("agency_id", ColumnData{});
    cols.emplace("route_short_name", ColumnData{});
    cols.emplace("route_long_name", ColumnData{});
    cols.emplace("route_desc", ColumnData{});
    cols.emplace("route_type", ColumnData{});
    cols.emplace("route_url", ColumnData{});
    cols.emplace("route_color", ColumnData{});
    cols.emplace("route_text_color", ColumnData{});
    cols.emplace("route_sort_order", ColumnData{});
    cols.emplace("continuous_pickup", ColumnData{});
    cols.emplace("continuous_drop_off", ColumnData{});

    cols["route_id"].isOptional            = false;
    cols["agency_id"].isOptional           = true;
    cols["route_short_name"].isOptional    = true;
    cols["route_long_name"].isOptional     = true;
    cols["route_desc"].isOptional          = true;
    cols["route_type"].isOptional          = false;
    cols["route_url"].isOptional           = true;
    cols["route_color"].isOptional         = true;
    cols["route_text_color"].isOptional    = true;
    cols["route_sort_order"].isOptional    = true;
    cols["continuous_pickup"].isOptional   = true;
    cols["continuous_drop_off"].isOptional = true;

    setColsToExist(csvData, cols);

    std::string route_id;
    for(auto const& row : csvData)
    {
        route_id = makeValue<std::string>(cols, "route_id", row);
        if(this->routes.count(route_id) > 0)
            throw std::domain_error(std::string("duplicate route_id \"") + route_id + "\" found in \"" + folder
                                    + "/routes.txt\"");
        this->routes.emplace(
        route_id,
        std::make_shared<Route>(Route(route_id,
                                      makeValue<std::optional<int>>(cols, "agency_id", row),
                                      makeValue<std::optional<std::string>>(cols, "route_short_name", row),
                                      makeValue<std::optional<std::string>>(cols, "route_long_name", row),
                                      makeValue<std::optional<std::string>>(cols, "route_desc", row),
                                      makeValue<Route::route_type_enum>(cols, "route_type", row),
                                      makeValue<std::optional<std::string>>(cols, "route_url", row),
                                      makeValue<std::optional<std::string>>(cols, "route_color", row),
                                      makeValue<std::optional<std::string>>(cols, "route_text_color", row),
                                      makeValue<std::optional<unsigned int>>(cols, "route_sort_order", row),
                                      makeValue<Route::continuous_pickup_enum>(cols, "continuous_pickup", row),
                                      makeValue<Route::continuous_drop_off_enum>(cols, "continuous_drop_off", row))));
    }

    int i = 0;
    for(const auto& route : this->routes)
    {
        std::cout << *(route.second) << std::endl;
        if(++i > this->maxPrint) break;
    }
}

void GTFS::readTrips(const std::string& folder)
{
    if(std::filesystem::exists(folder + "/trips.txt")) throw std::string(folder + "/trips.txt not found!");

    CSVReader csvData(folder + "/trips.txt");
    csvData.printCSV();

    map_t<std::string, ColumnData> cols;

    cols.emplace("route_id", ColumnData{});
    cols.emplace("service_id", ColumnData{});
    cols.emplace("trip_id", ColumnData{});
    cols.emplace("trip_headsign", ColumnData{});
    cols.emplace("trip_short_name", ColumnData{});
    cols.emplace("direction_id", ColumnData{});
    cols.emplace("block_id", ColumnData{});
    cols.emplace("shape_id", ColumnData{});
    cols.emplace("wheelchair_accessible", ColumnData{});
    cols.emplace("bikes_allowed", ColumnData{});

    cols["route_id"].isOptional              = false;
    cols["service_id"].isOptional            = false;
    cols["trip_id"].isOptional               = false;
    cols["trip_headsign"].isOptional         = true;
    cols["trip_short_name"].isOptional       = true;
    cols["direction_id"].isOptional          = true;
    cols["block_id"].isOptional              = true;
    cols["shape_id"].isOptional              = true;
    cols["wheelchair_accessible"].isOptional = true;
    cols["bikes_allowed"].isOptional         = true;

    setColsToExist(csvData, cols);

    int trip_id;
    for(auto const& row : csvData)
    {
        trip_id = makeValue<int>(cols, "trip_id", row);
        if(this->trips.count(trip_id) > 0)
            throw std::domain_error(std::string("duplicate trip_id \"") + std::to_string(trip_id) + "\" found in \""
                                    + folder + "/trips.txt\"");
        this->trips.emplace(
        trip_id,
        std::make_shared<Trip>(Trip(makeValue<std::string>(cols, "route_id", row),
                                    makeValue<int>(cols, "service_id", row),
                                    trip_id,
                                    makeValue<std::optional<std::string>>(cols, "trip_headsign", row),
                                    makeValue<std::optional<std::string>>(cols, "trip_short_name", row),
                                    makeValue<Trip::direction_id_enum>(cols, "direction_id", row),
                                    makeValue<std::optional<int>>(cols, "block_id", row),
                                    makeValue<std::optional<int>>(cols, "shape_id", row),
                                    makeValue<Trip::wheelchair_accessible_enum>(cols, "wheelchair_accessible", row),
                                    makeValue<Trip::bikes_allowed_enum>(cols, "bikes_allowed", row))));
    }
    int i = 0;
    for(const auto& trip : this->trips)
    {
        std::cout << *(trip.second) << std::endl;
        if(++i > this->maxPrint) break;
    }

    connectTripRoutesToRoutesId();
}

/* connect trips to other read files, fill its pointers */
void GTFS::connectTripRoutesToRoutesId()
{
    for(auto trip : this->trips) { trip.second->route = this->routes.at(trip.second->getRoute_id()); }
}


void GTFS::readStopTimes(const std::string& folder)
{
    if(std::filesystem::exists(folder + "/stop_times.txt")) throw std::string(folder + "/stop_times.txt not found!");

    CSVReader csvData(folder + "/stop_times.txt");
    csvData.printCSV();

    map_t<std::string, ColumnData> cols;

    cols.emplace("trip_id", ColumnData{});
    cols.emplace("arrival_time", ColumnData{});
    cols.emplace("departure_time", ColumnData{});
    cols.emplace("stop_id", ColumnData{});
    cols.emplace("stop_sequence", ColumnData{});
    cols.emplace("stop_headsign", ColumnData{});
    cols.emplace("pickup_type", ColumnData{});
    cols.emplace("drop_off_type", ColumnData{});
    cols.emplace("continuous_pickup", ColumnData{});
    cols.emplace("continuous_drop_off", ColumnData{});
    cols.emplace("shape_dist_traveled", ColumnData{});
    cols.emplace("timepoint", ColumnData{});

    cols["trip_id"].isOptional             = false;
    cols["arrival_time"].isOptional        = true;
    cols["departure_time"].isOptional      = true;
    cols["stop_id"].isOptional             = true;
    cols["stop_sequence"].isOptional       = false;
    cols["stop_headsign"].isOptional       = true;
    cols["pickup_type"].isOptional         = true;
    cols["drop_off_type"].isOptional       = true;
    cols["continuous_pickup"].isOptional   = true;
    cols["continuous_drop_off"].isOptional = true;
    cols["shape_dist_traveled"].isOptional = true;
    cols["timepoint"].isOptional           = true;

    setColsToExist(csvData, cols);

    for(auto const& row : csvData)
    {
        this->stop_times.emplace_back(std::make_shared<StopTime>(
        StopTime(makeValue<stop_times_types::trip_id_t>(cols, "trip_id", row),
                 makeValue<stop_times_types::arrival_time_t>(cols, "arrival_time", row),
                 makeValue<stop_times_types::departure_time_t>(cols, "departure_time", row),
                 makeValue<stop_times_types::stop_id_t>(cols, "stop_id", row),
                 makeValue<stop_times_types::stop_sequence_t>(cols, "stop_sequence", row),
                 makeValue<stop_times_types::stop_headsign_t>(cols, "stop_headsign", row),
                 makeValue<StopTime::pickup_type_enum>(cols, "pickup_type", row),
                 makeValue<StopTime::drop_off_type_enum>(cols, "drop_off_type", row),
                 makeValue<StopTime::continuous_pickup_enum>(cols, "continuous_pickup", row),
                 makeValue<StopTime::continuous_drop_off_enum>(cols, "continuous_drop_off", row),
                 makeValue<stop_times_types::shape_dist_traveled_t>(cols, "shape_dist_traveled", row),
                 makeValue<StopTime::timepoint_enum>(cols, "timepoint", row))));
    }
    for(size_t i = 0; i < this->stop_times.size() && i < this->maxPrint; i++)
    { std::cout << *this->stop_times[i] << std::endl; }

    connectStopTimesToTripsAndStops();
}

/* connect stop_times to other read files, fill its pointers */
void GTFS::connectStopTimesToTripsAndStops()
{
    std::cout << "/* connect stop_times to other read files, fill its pointers */" << std::endl;
    for(auto& stopService : this->stop_times)
    {
        // trip.second->route = this->routes.at(trip.second->getRoute_id());

        // trip
        const auto& tripId = stopService->getTrip_id();
        if(this->trips.count(tripId) > 0) stopService->trip = this->trips.at(tripId);

        // stop
        const auto& stopId = stopService->getStop_id();
        if(this->stops.count(stopId) > 0) stopService->stop = this->stops.at(stopId);
    }
}

void GTFS::readCalendar(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/calendar.txt"))
        std::cout << "optional file " + folder + "/calendar.txt" + " not found\n";

    CSVReader csvData(folder + "/calendar.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readCalendarDates(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/calendar_dates.txt"))
        std::cout << "optional file " + folder + "/calendar_dates.txt" + " not found\n";

    CSVReader csvData(folder + "/calendar_dates.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readFareAttributes(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/fare_attributes.txt"))
        std::cout << "optional file " + folder + "/fare_attributes.txt" + " not found\n";

    CSVReader csvData(folder + "/fare_attributes.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readFareRules(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/fare_rules.txt"))
        std::cout << "optional file " + folder + "/fare_rules.txt" + " not found\n";

    CSVReader csvData(folder + "/fare_rules.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readShapes(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/shapes.txt"))
        std::cout << "optional file " + folder + "/shapes.txt" + " not found\n";

    CSVReader csvData(folder + "/shapes.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readFrequencies(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/frequencies.txt"))
        std::cout << "optional file " + folder + "/frequencies.txt" + " not found\n";

    CSVReader csvData(folder + "/frequencies.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readTransfers(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/transfers.txt"))
        std::cout << "optional file " + folder + "/transfers.txt" + " not found\n";

    CSVReader csvData(folder + "/transfers.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readPathways(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/pathways.txt"))
        std::cout << "optional file " + folder + "/pathways.txt" + " not found\n";

    CSVReader csvData(folder + "/pathways.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readLevels(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/levels.txt"))
        std::cout << "optional file " + folder + "/levels.txt" + " not found\n";

    CSVReader csvData(folder + "/levels.txt");
    csvData.printCSV();
    csvData;
}

void GTFS::readFeedInfo(const std::string& folder)
{
    if(!std::filesystem::exists(folder + "/feed_info.txt"))
        std::cout << "optional file " + folder + "/feed_info.txt" + " not found\n";

    CSVReader csvData(folder + "/feed_info.txt");
    csvData.printCSV();
    csvData;
}


GTFS::GTFS(const std::string& folder)
{
    readAgency(folder);
    readStops(folder);
    readRoutes(folder);
    readTrips(folder);
    readStopTimes(folder);
    readCalendar(folder);
    readCalendarDates(folder);
    // readFareAttributes(folder);
    // readFareRules(folder);
    readShapes(folder);
    readFrequencies(folder);
    readTransfers(folder);
    readPathways(folder);
    // readLevels(folder);
    // readFeedInfo(folder);

    connectTripsStopTimes();

    auto trip = this->trips.begin()->second;
    std::cout << *trip << std::endl;
    for(auto a : trip->includedStopTimes)
    {
        std::cout << *a.second.lock() << std::endl;
        std::cout << *a.second.lock()->stop.lock() << std::endl;
    }
}

GTFS::~GTFS() { }

void GTFS::connectTripsStopTimes()
{
    std::cout << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
    for(auto const& stop_t : this->stop_times)
    {
        auto trip = stop_t->trip.lock();
        if(!trip)
        {
            std::cout << "warning, a stop_times does not have their trip connected!";
            continue;
        }
        trip->includedStopTimes.emplace(stop_t->getStop_sequence(), stop_t);
    }
}
