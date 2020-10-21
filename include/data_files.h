#ifndef DATA_FILES_H
#define DATA_FILES_H
#include <file_io.h>
#include <cstdio>
#include <vector>
#include <array>

class DataFileHandler {
    // Read/parse the leap seconds file
    void parse_leap_seconds();
public:
    // List of all known leap second times and values (sec. since J2000, Leap second value)
    std::vector<std::array<double, 2>> leap_seconds;

    // Default constructor
    DataFileHandler();

    // Get the number of leap seconds used in offset
    double get_leap_seconds(double seconds_since_j2000);
};

// Static reference to process's main DataFileHandler instance
static DataFileHandler DATA_FILES {};

#endif