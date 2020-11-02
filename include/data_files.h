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

    /*
    Read/parse the leap seconds file

    Open/parse the leap seconds file and add the values to the leap_seconds vector
    */
    void parse_leap_seconds();

    void parse_finals();

public:
    // List of all known leap second times and values (sec. since J2000, Leap second value)
    std::vector<std::array<double, 2>> leap_seconds;
    // List of finals.all data lines
    std::vector<std::array<double, 7>> finals_data;

    /*
    Default constructor

    Assigns member variables to empty vectors
    */
    DataFileHandler();

    /*
    Get the number of leap seconds used in offset

    Determine the leap seconds value to use for a given epoch
    @param seconds_since_j2000 Requested time given in seconds since J2000
    @returns (double) The leap second value at the given epoch
    */
    double get_leap_seconds(double seconds_since_j2000);

    /*
    Get the finals.all data at an epoch (modified Julian)

    @param mjd Modified Julian Date at which to find valid finals.all data
    @returns (std::array<double, 7>) finals.all data as a series of doubles
    */
    std::array<double, 7> get_finals(double mjd);
};

/*
Static instance of DataFileHandler

A singleton prevents repeated parsing of data files, saving I/O overhead
*/
static DataFileHandler DATA_FILES{};

#endif