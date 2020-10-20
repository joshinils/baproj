#include "GTFS.h"
#include "CSVReader.h"
#include <exception>
#include <filesystem>
#include <map>

template<typename T>
T makeValue(const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
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
std::optional<int> makeValue<std::optional<int>>(const std::map<std::string, GTFS::ColumnData>& cdMap,
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
std::optional<unsigned int> makeValue<std::optional<unsigned int>>(const std::map<std::string, GTFS::ColumnData>& cdMap,
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
std::optional<long long> makeValue<std::optional<long long>>(const std::map<std::string, GTFS::ColumnData>& cdMap,
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
int makeValue<int>(const std::map<std::string, GTFS::ColumnData>& cdMap,
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
unsigned int makeValue<unsigned int>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                     const std::string& name,
                                     const CSVReader::Row& row)
{
    const GTFS::ColumnData& cd = cdMap.at(name);
    if(cd.exists && !row[cd.index].empty() && !cd.isOptional) return std::stoul(row[cd.index]);
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
Stops::location_type_enum makeValue<Stops::location_type_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                               const std::string& name,
                                                               const CSVReader::Row& row)
{
    return Stops::location_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stops::wheelchair_boarding_enum makeValue<Stops::wheelchair_boarding_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stops::wheelchair_boarding_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Routes::route_type_enum makeValue<Routes::route_type_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                           const std::string& name,
                                                           const CSVReader::Row& row)
{
    auto rv = makeValue<std::optional<int>>(cdMap, name, row);
    if(rv.has_value()) return Routes::route_type_enum(rv.value());
    else
        throw std::domain_error("required field \"" + name + "\" does not exist!");
}

template<>
Routes::continuous_pickup_enum makeValue<Routes::continuous_pickup_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Routes::continuous_pickup_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Routes::continuous_drop_off_enum makeValue<Routes::continuous_drop_off_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Routes::continuous_drop_off_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trips::direction_id_enum makeValue<Trips::direction_id_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                             const std::string& name,
                                                             const CSVReader::Row& row)
{
    return Trips::direction_id_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trips::wheelchair_accessible_enum makeValue<Trips::wheelchair_accessible_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Trips::wheelchair_accessible_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Trips::bikes_allowed_enum makeValue<Trips::bikes_allowed_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                               const std::string& name,
                                                               const CSVReader::Row& row)
{
    return Trips::bikes_allowed_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop_times::pickup_type_enum makeValue<Stop_times::pickup_type_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stop_times::pickup_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop_times::drop_off_type_enum makeValue<Stop_times::drop_off_type_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stop_times::drop_off_type_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop_times::continuous_pickup_enum makeValue<Stop_times::continuous_pickup_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stop_times::continuous_pickup_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop_times::continuous_drop_off_enum makeValue<Stop_times::continuous_drop_off_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stop_times::continuous_drop_off_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
Stop_times::timepoint_enum makeValue<Stop_times::timepoint_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                                 const std::string& name,
                                                                 const CSVReader::Row& row)
{
    return Stop_times::timepoint_enum(makeValue<std::optional<int>>(cdMap, name, row).value_or(-1));
}

template<>
std::optional<double> makeValue<std::optional<double>>(const std::map<std::string, GTFS::ColumnData>& cdMap,
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

GTFS::GTFS(const std::string& folder)
{
    if(std::filesystem::exists(folder + "/agency.txt"))
    {
        CSVReader csvData(folder + "/agency.txt");
        csvData.printCSV();

        std::map<std::string, ColumnData> cols;

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

        int colIndex = 0;
        for(const auto& colName : csvData.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : csvData)
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
        for(size_t i = 0; i < this->agency.size() && i < this->maxPrint; i++)
        { std::cout << this->agency[i] << std::endl; }
    }
    else
    {
        throw std::string(folder + "/agency.txt not found!");
    }

    if(std::filesystem::exists(folder + "/stops.txt"))
    {
        CSVReader csvData(folder + "/stops.txt");
        csvData.printCSV();

        std::map<std::string, ColumnData> cols;

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

        int colIndex = 0;
        for(const auto& colName : csvData.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : csvData)
        {
            this->stops.emplace_back(Stops(makeValue<std::string>(cols, "stop_id", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_code", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_name", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_desc", row),
                                           makeValue<std::optional<double>>(cols, "stop_lat", row),
                                           makeValue<std::optional<double>>(cols, "stop_lon", row),
                                           makeValue<std::optional<std::string>>(cols, "zone_id", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_url", row),
                                           makeValue<Stops::location_type_enum>(cols, "location_type", row),
                                           makeValue<std::optional<long long>>(cols, "parent_station", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_timezone", row),
                                           makeValue<Stops::wheelchair_boarding_enum>(cols, "wheelchair_boarding", row),
                                           makeValue<std::optional<int>>(cols, "level_id", row),
                                           makeValue<std::optional<std::string>>(cols, "platform_code", row)));
        }
        for(size_t i = 0; i < this->stops.size() && i < this->maxPrint; i++)
        { std::cout << this->stops[i] << std::endl; }
    }
    else
    {
        throw std::string(folder + "/stops.txt not found!");
    }

    if(std::filesystem::exists(folder + "/routes.txt"))
    {
        CSVReader csvData(folder + "/routes.txt");
        csvData.printCSV();

        std::map<std::string, ColumnData> cols;

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

        int colIndex = 0;
        for(const auto& colName : csvData.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : csvData)
        {
            this->routes.emplace_back(
            Routes(makeValue<std::string>(cols, "route_id", row),
                   makeValue<std::optional<int>>(cols, "agency_id", row),
                   makeValue<std::optional<std::string>>(cols, "route_short_name", row),
                   makeValue<std::optional<std::string>>(cols, "route_long_name", row),
                   makeValue<std::optional<std::string>>(cols, "route_desc", row),
                   makeValue<Routes::route_type_enum>(cols, "route_type", row),
                   makeValue<std::optional<std::string>>(cols, "route_url", row),
                   makeValue<std::optional<std::string>>(cols, "route_color", row),
                   makeValue<std::optional<std::string>>(cols, "route_text_color", row),
                   makeValue<std::optional<unsigned int>>(cols, "route_sort_order", row),
                   makeValue<Routes::continuous_pickup_enum>(cols, "continuous_pickup", row),
                   makeValue<Routes::continuous_drop_off_enum>(cols, "continuous_drop_off", row)));
        }

        for(size_t i = 0; i < this->routes.size() && i < this->maxPrint; i++)
        { std::cout << this->routes[i] << std::endl; }
    }
    else
    {
        throw std::string(folder + "/routes.txt not found!");
    }

    if(std::filesystem::exists(folder + "/trips.txt"))
    {
        CSVReader csvData(folder + "/trips.txt");
        csvData.printCSV();

        std::map<std::string, ColumnData> cols;

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

        int colIndex = 0;
        for(const auto& colName : csvData.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : csvData)
        {
            this->trips.emplace_back(
            Trips(makeValue<std::string>(cols, "route_id", row),
                  makeValue<int>(cols, "service_id", row),
                  makeValue<int>(cols, "trip_id", row),
                  makeValue<std::optional<std::string>>(cols, "trip_headsign", row),
                  makeValue<std::optional<std::string>>(cols, "trip_short_name", row),
                  makeValue<Trips::direction_id_enum>(cols, "direction_id", row),
                  makeValue<std::optional<int>>(cols, "block_id", row),
                  makeValue<std::optional<int>>(cols, "shape_id", row),
                  makeValue<Trips::wheelchair_accessible_enum>(cols, "wheelchair_accessible", row),
                  makeValue<Trips::bikes_allowed_enum>(cols, "bikes_allowed", row)));
        }
        for(size_t i = 0; i < this->trips.size() && i < this->maxPrint; i++)
        { std::cout << this->trips[i] << std::endl; }
    }
    else
    {
        throw std::string(folder + "/trips.txt not found!");
    }

    if(std::filesystem::exists(folder + "/stop_times.txt"))
    {
        CSVReader csvData(folder + "/stop_times.txt");
        csvData.printCSV();

        std::map<std::string, ColumnData> cols;

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

        int colIndex = 0;
        for(const auto& colName : csvData.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : csvData)
        {
            this->stop_times.emplace_back(
            Stop_times(makeValue<int>(cols, "trip_id", row),
                       makeValue<std::optional<std::string>>(cols, "arrival_time", row),
                       makeValue<std::optional<std::string>>(cols, "departure_time", row),
                       makeValue<std::string>(cols, "stop_id", row),
                       makeValue<unsigned int>(cols, "stop_sequence", row),
                       makeValue<std::optional<std::string>>(cols, "stop_headsign", row),
                       makeValue<Stop_times::pickup_type_enum>(cols, "pickup_type", row),
                       makeValue<Stop_times::drop_off_type_enum>(cols, "drop_off_type", row),
                       makeValue<Stop_times::continuous_pickup_enum>(cols, "continuous_pickup", row),
                       makeValue<Stop_times::continuous_drop_off_enum>(cols, "continuous_drop_off", row),
                       makeValue<std::optional<double>>(cols, "shape_dist_traveled", row),
                       makeValue<Stop_times::timepoint_enum>(cols, "timepoint", row)));
        }
        for(size_t i = 0; i < this->stop_times.size() && i < this->maxPrint; i++)
        { std::cout << this->stop_times[i] << std::endl; }
    }
    else
    {
        throw std::string(folder + "/stop_times.txt not found!");
    }

    if(std::filesystem::exists(folder + "/calendar.txt"))
    {
        CSVReader csvData(folder + "/calendar.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/calendar.txt" + " not found\n";
    }

    if(std::filesystem::exists(folder + "/calendar_dates.txt"))
    {
        CSVReader csvData(folder + "/calendar_dates.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/calendar_dates.txt" + " not found\n";
    }

    // if(std::filesystem::exists(folder + "/fare_rules.txt"))
    // {
    //     CSVReader csvData(folder + "/fare_rules.txt");
    //     csvData.printCSV();
    //     csvData;
    // }
    // else
    // {
    //     std::cout << "optional file " + folder + "/fare_rules.txt" + " not found\n";
    // }

    // if(std::filesystem::exists(folder + "/fare_attributes.txt"))
    // {
    //     CSVReader csvData(folder + "/fare_attributes.txt");
    //     csvData.printCSV();
    //     csvData;
    // }
    // else
    // {
    //     std::cout << "optional file " + folder + "/fare_attributes.txt" + " not found\n";
    // }

    if(std::filesystem::exists(folder + "/shapes.txt"))
    {
        CSVReader csvData(folder + "/shapes.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/shapes.txt" + " not found\n";
    }

    if(std::filesystem::exists(folder + "/frequencies.txt"))
    {
        CSVReader csvData(folder + "/frequencies.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/frequencies.txt" + " not found\n";
    }

    if(std::filesystem::exists(folder + "/transfers.txt"))
    {
        CSVReader csvData(folder + "/transfers.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/transfers.txt" + " not found\n";
    }

    if(std::filesystem::exists(folder + "/pathways.txt"))
    {
        CSVReader csvData(folder + "/pathways.txt");
        csvData.printCSV();
        csvData;
    }
    else
    {
        std::cout << "optional file " + folder + "/pathways.txt" + " not found\n";
    }

    // if(std::filesystem::exists(folder + "/levels.txt"))
    // {
    //     CSVReader csvData(folder + "/levels.txt");
    //     csvData.printCSV();
    //     csvData;
    // }
    // else
    // {
    //     std::cout << "optional file " + folder + "/levels.txt" + " not found\n";
    // }

    // if(std::filesystem::exists(folder + "/feed_info.txt"))
    // {
    //     CSVReader csvData(folder + "/feed_info.txt");
    //     csvData.printCSV();
    //     csvData;
    // }
    // else
    // {
    //     std::cout << "optional file " + folder + "/feed_info.txt" + " not found\n";
    // }
}

GTFS::~GTFS() { }
