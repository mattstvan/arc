#ifndef UTCTIME_H
#define UTCTIME_H
#include <ctime>
#include <string>

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

  // Format date using strftime parameters
  std::string to_iso();

  // Increment time by a desired number of seconds
  UTCTime increment(double seconds);

  // Calculate the difference between the instance and another UTCTime
  double difference(UTCTime other);

  // Evaluates to true if UTCTime is equal to another
  bool equals(UTCTime other);
};

#endif