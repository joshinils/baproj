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
    return Stops::location_type_enum(makeValue<int>(cdMap, name, row));
}

template<>
Stops::wheelchair_boarding_enum makeValue<Stops::wheelchair_boarding_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Stops::wheelchair_boarding_enum(makeValue<int>(cdMap, name, row));
}

template<>
Routes::route_type_enum makeValue<Routes::route_type_enum>(const std::map<std::string, GTFS::ColumnData>& cdMap,
                                                           const std::string& name,
                                                           const CSVReader::Row& row)
{
    return Routes::route_type_enum(makeValue<int>(cdMap, name, row));
}

template<>
Routes::continuous_pickup_enum makeValue<Routes::continuous_pickup_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Routes::continuous_pickup_enum(makeValue<int>(cdMap, name, row));
}

template<>
Routes::continuous_drop_off_enum makeValue<Routes::continuous_drop_off_enum>(
const std::map<std::string, GTFS::ColumnData>& cdMap, const std::string& name, const CSVReader::Row& row)
{
    return Routes::continuous_drop_off_enum(makeValue<int>(cdMap, name, row));
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
        CSVReader agency(folder + "/agency.txt");
        agency.printCSV();

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
        for(const auto& colName : agency.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : agency)
        {
            this->agency.emplace_back(Agency(makeValue<std::optional<std::string>>(cols, "agency_id", row),
                                             makeValue<std::string>(cols, "agency_name", row),
                                             makeValue<std::string>(cols, "agency_url", row),
                                             makeValue<std::string>(cols, "agency_timezone", row),
                                             makeValue<std::optional<std::string>>(cols, "agency_lang", row),
                                             makeValue<std::optional<std::string>>(cols, "agency_phone", row),
                                             makeValue<std::optional<std::string>>(cols, "agency_fare_url", row),
                                             makeValue<std::optional<std::string>>(cols, "agency_email", row)));
        }
        for(auto row : this->agency) std::cout << row << std::endl;
    }
    else
    {
        throw std::string(folder + "/agency.txt not found!");
    }

    if(std::filesystem::exists(folder + "/stops.txt"))
    {
        CSVReader stops(folder + "/stops.txt");
        stops.printCSV();

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
        for(const auto& colName : stops.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : stops)
        {
            this->stops.emplace_back(Stops(makeValue<std::string>(cols, "stop_id", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_code", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_name", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_desc", row),
                                           makeValue<std::optional<double>>(cols, "stop_lat", row),
                                           makeValue<std::optional<double>>(cols, "stop_lon", row),
                                           makeValue<std::optional<int>>(cols, "zone_id", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_url", row),
                                           makeValue<Stops::location_type_enum>(cols, "location_type", row),
                                           makeValue<std::optional<long long>>(cols, "parent_station", row),
                                           makeValue<std::optional<std::string>>(cols, "stop_timezone", row),
                                           makeValue<Stops::wheelchair_boarding_enum>(cols, "wheelchair_boarding", row),
                                           makeValue<std::optional<int>>(cols, "level_id", row),
                                           makeValue<std::optional<std::string>>(cols, "platform_code", row)));
        }
        for(auto row : this->stops) std::cout << row << std::endl;
    }
    else
    {
        throw std::string(folder + "/stops.txt not found!");
    }


    if(std::filesystem::exists(folder + "/routes.txt"))
    {
        CSVReader routes(folder + "/routes.txt");
        routes.printCSV();

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
        for(const auto& colName : routes.getHeader())
        {
            cols[colName].exists = true;
            cols[colName].index  = colIndex;
            ++colIndex;
        }

        for(auto row : routes)
        {
            // std::optional<std::string>
            // std::optional<std::string>
            // std::optional<std::string>
            // route_type_enum
            // std::optional<std::string>
            // std::optional<std::string>
            // std::optional<std::string>
            // std::optional<unsigned int>
            // continuous_pickup_enum
            // continuous_drop_off_enum

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
        for(auto row : this->routes) std::cout << row << std::endl;
    }
    else
    {
        throw std::string(folder + "/routes.txt not found!");
    }


    if(std::filesystem::exists(folder + "/trips.txt"))
    {
        CSVReader trips(folder + "/trips.txt");
        trips.printCSV();
        trips;
    }
    else
    {
        throw std::string(folder + "/trips.txt not found!");
    }


    if(std::filesystem::exists(folder + "/stop_times.txt"))
    {
        CSVReader stop_times(folder + "/stop_times.txt");
        stop_times.printCSV();
        stop_times;
    }
    else
    {
        throw std::string(folder + "/stop_times.txt not found!");
    }


    if(std::filesystem::exists(folder + "/calendar.txt"))
    {
        CSVReader calendar(folder + "/calendar.txt");
        calendar.printCSV();
        calendar;
    }

    if(std::filesystem::exists(folder + "/calendar_dates.txt"))
    {
        CSVReader calendar_dates(folder + "/calendar_dates.txt");
        calendar_dates.printCSV();
        calendar_dates;
    }

    if(std::filesystem::exists(folder + "/fare_rules.txt"))
    {
        CSVReader fare_rules(folder + "/fare_rules.txt");
        fare_rules.printCSV();
        fare_rules;
    }

    if(std::filesystem::exists(folder + "/fare_attributes.txt"))
    {
        CSVReader fare_attributes(folder + "/fare_attributes.txt");
        fare_attributes.printCSV();
        fare_attributes;
    }

    if(std::filesystem::exists(folder + "/shapes.txt"))
    {
        CSVReader shapes(folder + "/shapes.txt");
        shapes.printCSV();
        shapes;
    }

    if(std::filesystem::exists(folder + "/frequencies.txt"))
    {
        CSVReader frequencies(folder + "/frequencies.txt");
        frequencies.printCSV();
        frequencies;
    }

    if(std::filesystem::exists(folder + "/transfers.txt"))
    {
        CSVReader transfers(folder + "/transfers.txt");
        transfers.printCSV();
        transfers;
    }

    if(std::filesystem::exists(folder + "/pathways.txt"))
    {
        CSVReader pathways(folder + "/pathways.txt");
        pathways.printCSV();
        pathways;
    }

    if(std::filesystem::exists(folder + "/levels.txt"))
    {
        CSVReader levels(folder + "/levels.txt");
        levels.printCSV();
        levels;
    }

    if(std::filesystem::exists(folder + "/feed_info.txt"))
    {
        CSVReader feed_info(folder + "/feed_info.txt");
        feed_info.printCSV();
        feed_info;
    }
}

GTFS::~GTFS() { }
