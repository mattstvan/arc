#ifndef DATETIME_H
#define DATETIME_H
#include <ctime>
#include <string>

// Unix timestamp of J2000
const double UNIX_J2000 = 946727935.815918;

/*
Time scales

Available scales to use when representing a date/time
*/
enum TimeScale {
  // Coordinated Universal Time
  UTC,
  // Universal Time
  UT1,
  // International Atomic Time
  TAI,
  // Terrestrial Time
  TT,
  // Barycentric Dynamical Time
  TDB
};

// Return string representation of a TimeScale
std::string time_scale_str(TimeScale scale);

/*
Date and Time

Ref: Montenbruck, O., & Gill, E. (2012). Time and Reference Systems
In Satellite orbits: Models, methods, and applications (pp. 157-169). Berlin: Springer-Verlag.
*/
class DateTime {
public:
  // Number of seconds since J2000 (1 Jan 2000 12:00:00 TT)
  double seconds_since_j2000;
  // Time scale in which this DateTime is represented
  TimeScale scale;

  // Default constructor (J2000)
  DateTime();

  // Constructor using double
  DateTime(double seconds, TimeScale scale=UTC);

  // Constructor using input char* and format
  DateTime(std::string datestr, std::string format, TimeScale scale=UTC);

  // Constructor using input string in ISO 8601 format:
  // YYYY-MM-DDTHH:MM:SS.FFFFFF
  DateTime(std::string datestr, TimeScale scale=UTC);

  // Convert to `struct tm' representation of *TIMER in Universal Coordinated
  // Time
  tm* to_tm();

  // Get Unix timestamp of instance
  double unix_timestamp();

  // Convert to a Julian Date
  double julian_date();

  // Convert to Julian Centuries
  double julian_centuries();

  // Convert to UNSO Modified Julian Date
  double mjd();

  // Convert to GSFC Modified Julian Date
  double mjd_gsfc();

  // Convert to UT1
  DateTime ut1();

  // Convert to an International Atomic Time (TAI)
  DateTime tai();

  // Convert to a Terrestrial Time (TT)
  DateTime tt();

  // Convert to a Barycentric Dynamical Time (TDB)
  DateTime tdb();

  // Calculate the Greenwich Mean Sideral Time (GMST) angle in radians
  double gmst_angle();

  // Increment time by a desired number of seconds
  DateTime increment(double seconds);

  // Calculate the difference between the instance and another UTCTime
  double difference(DateTime& other);

  // Evaluates to true if UTCTime is equal to another
  bool equals(DateTime& other);

  // Format date using strftime parameters
  std::string format(char fmt[]);

  // Format date usding strftime paramaters, adding fractional seconds
  std::string format_fractional(char fmt[]);

  // Format date as ISO 8601
  std::string to_iso();
};

// I/O stream 
std::ostream& operator << (std::ostream &out, DateTime& dt);

#endif