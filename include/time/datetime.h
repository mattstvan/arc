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

  /*
  Default constructor

  Sets seconds_since_j2000 to 0.0 using UTC time scale
  */
  DateTime();

  /*
  Constructor using double and TimeScale

  @param seconds Number of seconds (positive or negative) since J2000
  @param scale Time scale in which this DateTime is represented (default is UTC)
  */
  DateTime(double seconds, TimeScale scale = UTC);

  /*
  Constructor using input string and format

  @param datestr String representing the date
  @param datestr String representing the format of the date, using strftime
  parameters
  @param scale Time scale in which this DateTime is represented (default is UTC)
  */
  DateTime(std::string datestr, std::string format, TimeScale scale = UTC);

  /*
  Constructor using input string in ISO 8601 format:
  YYYY-MM-DDTHH:MM:SS.FFFFFF

  @param datestr String representing the date
  @param scale Time scale in which this DateTime is represented (default is UTC)
  */
  DateTime(std::string datestr, TimeScale scale = UTC);

  // Convert to `struct tm' representation of *TIMER in UTC
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

  /*
  Convert to equivalent time in the UT1 time scale

  @returns (datetime::DateTime) This time in the UT1 scale
  */
  DateTime ut1();

  /*
  Convert to equivalent time in the International Atomic Time (TAI) scale

  @returns (datetime::DateTime) This time in the TAI scale
  */
  DateTime tai();

  /*
  Convert to equivalent time in the Terrestrial Time (TT) scale

  @returns (datetime::DateTime) This time in the TT scale
  */
  DateTime tt();

  /*
  Convert to equivalent time in the Barycentric Dynamical Time (TDB) scale

  @returns (datetime::DateTime) This time in the TDB scale
  */
  DateTime tdb();

  /*
  Calculate the Greenwich Mean Sideral Time (GMST) angle

  @returns (double) This time as a GMST angle in radians
  */
  double gmst_angle();

  /*
  Increment time by a desired number of seconds

  @param seconds Number of seconds to increment the time (can be negative)
  @returns (datetime::DateTime) New instance representing this plus the seconds
  argument
  */
  DateTime increment(double seconds);

  /*
  Calculate the difference between this instance and another DateTime

  @param other DateTime instance to compare
  @returns (double) Number of total seconds elapsed since DateTime other
  */
  double difference(DateTime& other);

  /*
  Evaluates to true if DateTime is equal to another

  @param other DateTime instance to compare
  @returns (bool) Evaluation of the comparison
  */
  bool equals(DateTime& other);

  /*
  Format date using strftime parameters

  @param fmt Format (using strftime syntax) to use for formatting the date
  @returns (std::string) Formatted date/time
  */
  std::string format(const char fmt[]);

  /*
  Format date usding strftime paramaters, appending fractional seconds

  @param fmt Format (using strftime syntax) to use for formatting the date
  @returns (std::string) Formatted date/time with fractional seconds suffix
  */
  std::string format_fractional(const char fmt[]);

  /*
  Format date as ISO 8601

  @returns (std::string) Date/time formatted using ISO 8601 standard
  */
  std::string to_iso();
};

// I/O stream 
std::ostream& operator << (std::ostream& out, DateTime& dt);

#endif