#include <data_files.h>

/*
DataFileHandler methods
*/

/*
Default constructor

Assigns member variables to empty vectors
*/
DataFileHandler::DataFileHandler() {
  this->leap_seconds = std::vector<std::array<double, 2>>{};
  this->finals_data = std::vector<std::array<double, 7>>{};
}

/*
Read/parse the leap seconds file

Open/parse the leap seconds file and add the values to the leap_seconds vector
*/
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
      std::array<double, 2> values{(double)secs, (double)val};
      leap_seconds.push_back(values);
    }
  }
}

/*
Get the number of leap seconds used in offset

Determine the leap seconds value to use for a given epoch
@param seconds_since_j2000 Requested time given in seconds since J2000
@returns (double) The leap second value at the given epoch
*/
double DataFileHandler::get_leap_seconds(double seconds_since_j2000) {
  // If the leap seconds file has not yet been read
  if (leap_seconds.size() == 0) {
    parse_leap_seconds();
  }
  // If the requested time is after the last known leap second
  if (seconds_since_j2000 > leap_seconds[leap_seconds.size() - 1][0]) {
    // Return the latest leap second value
    return leap_seconds[leap_seconds.size() - 1][1];
  } else if (seconds_since_j2000 < leap_seconds[0][0]) {
    // If the requested time is before the first known leap second
    return 0.0;
  } else {
    // Iterate through the known leap seconds, excluding the last (case is
    // handled in first conditional)
    for (int i = 0; i < leap_seconds.size() - 2; i++) {
      // If the timestamp is between the current epoch and the next
      if (leap_seconds[i][0] <= seconds_since_j2000 &&
          seconds_since_j2000 < leap_seconds[i + 1][0]) {
        // Return the leap second value
        return leap_seconds[i][1];
      }
    }
    // This condition should never be met, but to be safe, return something if
    // every conditional fails
    return 0.0;
  }
}

/*
Get the finals.all data at an epoch (modified Julian)

@param mjd Modified Julian Date at which to find valid finals.all data
@returns (std::array<double, 7>) finals.all data as a series of doubles
*/
std::array<double, 7> DataFileHandler::get_finals(double mjd) {
  // Placeholder
  return std::array<double, 7>{0, 0, 0, 0, 0, 0, 0};
}
