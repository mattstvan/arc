#include <data_files.h>

/*
DataFileHandler methods
*/

// Default constructor
DataFileHandler::DataFileHandler() {
    this->leap_seconds = std::vector<std::array<double, 2>>{};
}

// Read/parse the leap seconds file
void DataFileHandler::parse_leap_seconds() {
    // Read the leap second file
    std::vector<std::string> lines = read_lines_from_file("data/leap_second.txt");
    // Iterate through the leap seconds file
    for (std::string l : lines) {
        float secs, val;
        // Grab the J2000+ seconds and leap values from the line
        sscanf(l.c_str(), "%f %f", &secs, &val);
        // Sanity check
        if (secs != 0 && val != 0) {
            // Add the values to the known leap seconds
            std::array<double, 2> values { (double)secs, (double)val };
            leap_seconds.push_back(values);
        }
    }
}

// Get the number of leap seconds used in offset
double DataFileHandler::get_leap_seconds(double seconds_since_j2000) {
    // If the leap seconds file has not yet been read
    if (leap_seconds.size() == 0) {
        parse_leap_seconds();
    }
    // If the requested time is after the last known leap second
    if (seconds_since_j2000 > leap_seconds[leap_seconds.size() - 1][0]) {
        // Return the latest leap second value
        return leap_seconds[leap_seconds.size() - 1][1];
    }
    else if (seconds_since_j2000 < leap_seconds[0][0]) {
        // If the requested time is before the first known leap second
        return 0.0;
    }
    else {
        // Iterate through the known leap seconds, excluding the last (case is handled in first conditional)
        for (int i = 0; i < leap_seconds.size() - 2; i++) {
            // If the timestamp is between the current epoch and the next
            if (leap_seconds[i][0] <= seconds_since_j2000 && seconds_since_j2000 < leap_seconds[i + 1][0]) {
                // Return the leap second value
                return leap_seconds[i][1];
            }
        }
    }
}

