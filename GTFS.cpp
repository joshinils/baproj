#include "GTFS.h"
#include "CSVReader.h"
#include <filesystem>

GTFS::GTFS(const std::string& folder)
{
    if(std::filesystem::exists(folder + "/agency.txt"))
    {
        CSVReader agency(folder + "/agency.txt");
        agency.printCSV();
        for(auto row : agency) this->agency.push_back(Agency(agency.getHeader(), row));
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
        stops;
    }
    else
    {
        throw std::string(folder + "/stops.txt not found!");
    }


    if(std::filesystem::exists(folder + "/routes.txt"))
    {
        CSVReader routes(folder + "/routes.txt");
        routes.printCSV();
        routes;
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
