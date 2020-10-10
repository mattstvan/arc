#ifndef UTCTIME_H
#define UTCTIME_H
#include <math.h>

#include <ctime>
#include <iostream>
#include <string>

// Unix timestamp of J2000
const double UNIX_J2000 = 946727935.816;

// UTC Date and Time
class UTCTime {
 public:
  double seconds_since_j2000;

  // Default constructor (J2000)
  UTCTime();

  // Constructor using double
  UTCTime(double seconds);

  // Constructor using long
  UTCTime(long seconds);

  // Print to std::cout
  void print();

  // Convert to `struct tm' representation of *TIMER in Universal Coordinated
  // Time
  tm* to_tm();

  // Get Unix timestamp of instance
  double unix();

  // Format date using strftime parameters
  std::string format(char fmt[]);

  // Format date usding strftime paramaters, adding fractional seconds
  std::string UTCTime::format_fractional(char fmt[]);

  // Format date as ISO 8601
  std::string to_iso();

  // Increment time by a desired number of seconds
  UTCTime increment(double seconds);

  // Calculate the difference between the instance and another UTCTime
  double difference(UTCTime other);

  // Evaluates to true if UTCTime is equal to another
  bool equals(UTCTime other);
};

#endif