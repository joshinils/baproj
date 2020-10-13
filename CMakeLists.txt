cmake_minimum_required(VERSION 3.10)
project(baproject VERSION 1.0.0)

add_executable("${PROJECT_NAME}" 
    "main.cpp"
    "CSVReader.h"
    "CSVReader.cpp"
)
