#include <utctime.h>

#include <ctime>
#include <iostream>

/*
UTC Date and Time methods
*/

// Default constructor (J2000)
UTCTime::UTCTime() { this->seconds_since_j2000 = 0.0; }

// Constructor using double
UTCTime::UTCTime(double seconds) { this->seconds_since_j2000 = seconds; }

// Constructor using long
UTCTime::UTCTime(long seconds) { this->seconds_since_j2000 = (double)seconds; }

// Print to std::cout
void UTCTime::print() {
  std::cout << "[UTCTime] { Seconds since J2000: " << seconds_since_j2000
            << ", ISO: " << to_iso() << " }" << std::endl;
}

// Convert to `struct tm' representation of *TIMER in Universal Coordinated Time
tm* UTCTime::to_tm() {
  time_t t = (long)(seconds_since_j2000 + 946727935.816);
  return gmtime(&t);
}

// Increment time by a desired number of seconds
UTCTime UTCTime::increment(double seconds) {
  return UTCTime {seconds_since_j2000 + seconds};
}

// Calculate the difference between the instance and another UTCTime
double UTCTime::difference(UTCTime other) {
  return seconds_since_j2000 - other.seconds_since_j2000;
}

// Evaluates to true if UTCTime is equal to another
bool UTCTime::equals(UTCTime other) {
  return seconds_since_j2000 == other.seconds_since_j2000;
}

// Format date as ISO string
std::string UTCTime::to_iso() {
  tm* t = to_tm();
  char buffer[256];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", t);
  return std::string{buffer};
}