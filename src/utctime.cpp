#include <utctime.h>
#include <stdexcept> 

/*
UTC Date and Time methods
*/

// Default constructor (J2000)
UTCTime::UTCTime() { this->seconds_since_j2000 = 0.0; }

// Constructor using double
UTCTime::UTCTime(double seconds) { this->seconds_since_j2000 = seconds; }

// Constructor using input char* and format
UTCTime::UTCTime(char datestr[], char format[]) {
  struct tm tm;
  strptime(datestr, format, &tm);
  this->seconds_since_j2000 = (double)mktime(&tm) - timezone - UNIX_J2000;
}

// Constructor using input char* in ISO 8601 format:
// YYYY-MM-DDTHH:MM:SS.FFFFFF
UTCTime::UTCTime(char datestr[]) {
  struct tm tm;
  strptime(datestr, "%Y-%m-%dT%H:%M:%S", &tm);
  std::string new_date_str = std::string{datestr};
  double dbl_fractional;
  try {
    std::string fractional = new_date_str.substr(new_date_str.find("."), new_date_str.size()-1);
    dbl_fractional = std::stod(fractional);
  } catch(const std::out_of_range& oor) {
    dbl_fractional = 0.0;
  }
  this->seconds_since_j2000 = (double)mktime(&tm) - timezone - UNIX_J2000 + dbl_fractional;  
}

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
double UTCTime::unix() { return seconds_since_j2000 + UNIX_J2000; }

// Increment time by a desired number of seconds
UTCTime UTCTime::increment(double seconds) {
  return UTCTime{seconds_since_j2000 + seconds};
}

// Calculate the difference between the instance and another UTCTime
double UTCTime::difference(UTCTime other) {
  return seconds_since_j2000 - other.seconds_since_j2000;
}

// Evaluates to true if UTCTime is equal to another
bool UTCTime::equals(UTCTime other) {
  return seconds_since_j2000 == other.seconds_since_j2000;
}

// Format date using strftime parameters
std::string UTCTime::format(char fmt[]) {
  tm* t = to_tm();
  char buffer[256];
  strftime(buffer, sizeof(buffer), fmt, t);
  return std::string{buffer};
}

// Format date usding strftime paramaters, adding fractional seconds
std::string UTCTime::format_fractional(char fmt[]) {
  std::string formatted = format(fmt);
  double unix = this->unix();
  double intpart = 1.0;
  std::string fractional = std::to_string(modf(unix, &intpart));
  fractional = fractional.substr(1, fractional.size());
  return formatted + fractional;
}

// Format date as ISO 8601
std::string UTCTime::to_iso() { return format_fractional("%Y-%m-%dT%H:%M:%S"); }