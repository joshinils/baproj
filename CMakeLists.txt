cmake_minimum_required(VERSION 3.10)
project(baproject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable("${PROJECT_NAME}"
    "agency.cpp"
    "agency.h"
    "calendar.cpp"
    "calendarDate.cpp"
    "calendarDate.h"
    "calendar.h"
    "CSVReader.cpp"
    "CSVReader.h"
    "fareAttribute.cpp"
    "fareAttribute.h"
    "fareRule.cpp"
    "fareRule.h"
    "feed_info.cpp"
    "feed_info.h"
    "frequencies.cpp"
    "frequencies.h"
    "GTFS.cpp"
    "GTFS.h"
    "level.cpp"
    "level.h"
    "main.cpp"
    "pathways.cpp"
    "pathways.h"
    "route.cpp"
    "route.h"
    "shape.cpp"
    "shape.h"
    "stop.cpp"
    "stop.h"
    "stopTime.cpp"
    "stopTime.h"
    "transfer.cpp"
    "transfer.h"
    "trip.cpp"
    "trip.h"
    "type_aliases.h"
    "TimePoint.h"
    "TimePoint.cpp"
)
