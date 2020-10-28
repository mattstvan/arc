#ifndef DATA_FILES_H
#define DATA_FILES_H
#include <file_io.h>
#include <cstdio>
#include <vector>
#include <array>

/*
Class to handle numerous data file types, such as
Earth Orientation Parameter files, leap second announcements, etc
*/
class DataFileHandler {

    void parse_leap_seconds();

    void parse_finals();

public:
    // List of all known leap second times and values (sec. since J2000, Leap second value)
    std::vector<std::array<double, 2>> leap_seconds;
    // List of finals.all data lines
    std::vector<std::array<double, 7>> finals_data;

    DataFileHandler();

    double get_leap_seconds(double seconds_since_j2000);

    std::array<double, 7> get_finals(double mjd);
};

/*
Static instance of DataFileHandler

A singleton prevents repeated parsing of data files, saving I/O overhead
*/
static DataFileHandler DATA_FILES{};

#endif