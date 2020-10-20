#include <utctime.h>
#include <stdexcept> 
#include <sstream>
#include <iomanip>
#include <bsd_strptime.h>

/*
UTC Date and Time methods
*/

// Default constructor (J2000)
UTCTime::UTCTime() { this->seconds_since_j2000 = 0.0; }

// Constructor using double
UTCTime::UTCTime(double seconds) { this->seconds_since_j2000 = seconds; }

// Constructor using input char* and format
UTCTime::UTCTime(std::string datestr, std::string format) {
  // Determine timezone and get offset
  time_t t = time(NULL);
  struct tm lt = { 0 };
  double offset = t - mktime(gmtime(&t));
  // Strip the date elements using NetBSD's strptime function
  bsd_strptime(datestr.c_str(), format.c_str(), &lt);
  // Parse any milliseconds from the end of the date string
  double dbl_millisecs;
  try {
    std::string fractional = datestr.substr(datestr.find("."), datestr.size() - 1);
    dbl_millisecs = std::stod(fractional);
  }
  catch (const std::out_of_range& err) {
    // If the parsing fails, assume no milliseconds were found
    dbl_millisecs = 0.0;
  }

  // Take the unix timestamp given by mktime, add the local GMT offset and any milliseconds, then offset by the unix timestamp of J2000
  this->seconds_since_j2000 = mktime(&lt) + offset - UNIX_J2000 + dbl_millisecs;
}

// Constructor using input char* in ISO 8601 format:
// YYYY-MM-DDTHH:MM:SS.FFFFFF
UTCTime::UTCTime(std::string datestr) : UTCTime{ datestr, "%Y-%m-%dT%H:%M:%S" } {}

// Print to std::cout
void UTCTime::print() {
  std::cout << "[UTCTime] { Seconds since J2000: " << seconds_since_j2000
    << ", ISO: " << to_iso() << " }" << std::endl;
}

// Convert to `struct tm' representation of *TIMER in Universal Coordinated Time
tm* UTCTime::to_tm() {
  time_t t = (long)(seconds_since_j2000 + UNIX_J2000);
  return gmtime(&t);
}

// Get Unix timestamp of instance
double UTCTime::unix_timestamp() { return seconds_since_j2000 + UNIX_J2000; }

// Increment time by a desired number of seconds
UTCTime UTCTime::increment(double seconds) {
  return UTCTime{ seconds_since_j2000 + seconds };
}

// Calculate the difference between the instance and another UTCTime
double UTCTime::difference(UTCTime &other) {
  return seconds_since_j2000 - other.seconds_since_j2000;
}

// Evaluates to true if UTCTime is equal to another
bool UTCTime::equals(UTCTime &other) {
  return seconds_since_j2000 == other.seconds_since_j2000;
}

// Format date using strftime parameters
std::string UTCTime::format(char fmt[]) {
  tm* t = to_tm();
  char buffer[256];
  strftime(buffer, sizeof(buffer), fmt, t);
  return std::string{ buffer };
}

// Format date usding strftime paramaters, adding fractional seconds
std::string UTCTime::format_fractional(char fmt[]) {
  std::string formatted = format(fmt);
  double timestamp = unix_timestamp();
  double intpart = 1.0;
  std::string fractional = std::to_string(modf(timestamp, &intpart));
  fractional = fractional.substr(fractional.find("."), fractional.size());
  return formatted + fractional;
}

// Format date as ISO 8601
std::string UTCTime::to_iso() { return format_fractional("%Y-%m-%dT%H:%M:%S"); }