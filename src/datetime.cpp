#include <datetime.h>
#include <stdexcept> 
#include <sstream>
#include <iomanip>
#include <bsd_strptime.h>
#include <data_files.h>
#include <math_utils.h>

/* Time scale methods */

// Return string representation of a TimeScale
std::string time_scale_str(TimeScale scale) {
  switch (scale) {
  case 0:
    return "UTC";
  case 1:
    return "UT1";
  case 2:
    return "TAI";
  case 3:
    return "TT";
  case 4:
    return "TDB";
  default:
    return "";
  }
}

/*
Date and Time methods
*/

/*
Default constructor

Sets seconds_since_j2000 to 0.0 using UTC time scale
*/
DateTime::DateTime() { this->seconds_since_j2000 = 0.0; this->scale = UTC; }

/*
Constructor using double and TimeScale

@param seconds Number of seconds (positive or negative) since J2000
@param scale Time scale in which this DateTime is represented (default is UTC)
*/
DateTime::DateTime(double seconds, TimeScale scale) { this->seconds_since_j2000 = seconds; this->scale = scale; }

/*
Constructor using input string and format

@param datestr String representing the date
@param datestr String representing the format of the date, using strftime parameters
@param scale Time scale in which this DateTime is represented (default is UTC)
*/
DateTime::DateTime(std::string datestr, std::string format, TimeScale scale) {
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
  this->scale = scale;
}

/*
Constructor using input string in ISO 8601 format:
YYYY-MM-DDTHH:MM:SS.FFFFFF

@param datestr String representing the date
@param scale Time scale in which this DateTime is represented (default is UTC)
*/
DateTime::DateTime(std::string datestr, TimeScale scale) : DateTime{ datestr, "%Y-%m-%dT%H:%M:%S", scale } {}

// Convert to `struct tm' representation of *TIMER in Universal Coordinated Time
tm* DateTime::to_tm() {
  time_t t = (long)(seconds_since_j2000 + UNIX_J2000);
  return gmtime(&t);
}

// Get Unix timestamp of instance
double DateTime::unix_timestamp() { return seconds_since_j2000 + UNIX_J2000; }

// Convert to a Julian Date
// Uses Unix time definition of Julian Day
double DateTime::julian_date() {
  return unix_timestamp() / 86400 + 2440587.5;
}

// Convert to Julian Centuries
// Uses Unix time definition of Julian Day
double DateTime::julian_centuries() {
  return (julian_date() - 2451545.0) / 36525.0;
}

// Convert to UNSO Modified Julian Date
double DateTime::mjd() {
  return julian_date() - 2400000.5;
}

// Convert to GSFC Modified Julian Date
double DateTime::mjd_gsfc() {
  return mjd() - 29999.5;
}

/*
Convert to equivalent time in the UT1 time scale

@returns (datetime::DateTime) This time in the UT1 scale
*/
DateTime DateTime::ut1() {
  double d_ut1 = DATA_FILES.get_finals(mjd())[3];
  return DateTime{ seconds_since_j2000 + d_ut1, UT1 };
}

/*
Convert to equivalent time in the International Atomic Time (TAI) scale

@returns (datetime::DateTime) This time in the TAI scale
*/ 
DateTime DateTime::tai() {
  double leap = DATA_FILES.get_leap_seconds(seconds_since_j2000);
  return DateTime{ seconds_since_j2000 + leap, TAI };
}

/*
Convert to equivalent time in the Terrestrial Time (TT) scale

@returns (datetime::DateTime) This time in the TT scale
*/
DateTime DateTime::tt() {
  DateTime dt_tai = tai();
  return { dt_tai.seconds_since_j2000 + 32.184, TT };
}

/*
Convert to equivalent time in the Barycentric Dynamical Time (TDB) scale

@returns (datetime::DateTime) This time in the TDB scale
*/
DateTime DateTime::tdb() {
  // Get this in Terrestrial Time
  DateTime dt_tt = tt();
  // Convert TT of this to Julian Centuries
  double jc = dt_tt.julian_centuries();
  // Calculate offset from unix time
  double m_earth = (357.5277233 + 35999.05034 * jc) * (M_PI / 180);
  double secs = 0.001658 * sin(m_earth) + 0.00001385 * sin(2 * m_earth);
  return DateTime{ dt_tt.seconds_since_j2000 + secs, TDB };
}

/*
Calculate the Greenwich Mean Sideral Time (GMST) angle

@returns (double) This time as a GMST angle in radians
*/
double DateTime::gmst_angle() {
  double t = ut1().julian_centuries();
  double seconds = eval_poly(t, std::vector<double> {
    67310.54841,
      876600.0 * 3600.0 + 8640184.812866,
      0.093104,
      6.2e-6
  });
  return (fmod(seconds, 86400) / 86400) * 2 * M_PI;
}

/*
Increment time by a desired number of seconds

@param seconds Number of seconds to increment the time (can be negative)
@returns (datetime::DateTime) New instance representing this plus the seconds argument
*/
DateTime DateTime::increment(double seconds) {
  return DateTime{ seconds_since_j2000 + seconds, scale };
}

/*
Calculate the difference between this instance and another DateTime

@param other DateTime instance to compare
@returns (double) Number of total seconds elapsed since DateTime other
*/
double DateTime::difference(DateTime& other) {
  return seconds_since_j2000 - other.seconds_since_j2000;
}

/*
Evaluates to true if DateTime is equal to another

@param other DateTime instance to compare
@returns (bool) Evaluation of the comparison
*/
bool DateTime::equals(DateTime& other) {
  return seconds_since_j2000 == other.seconds_since_j2000;
}

/*
Format date using strftime parameters

@param fmt Format (using strftime syntax) to use for formatting the date
@returns (std::string) Formatted date/time
*/
std::string DateTime::format(char fmt[]) {
  tm* t = to_tm();
  char buffer[256];
  strftime(buffer, sizeof(buffer), fmt, t);
  return std::string{ buffer };
}

/*
Format date usding strftime paramaters, appending fractional seconds

@param fmt Format (using strftime syntax) to use for formatting the date
@returns (std::string) Formatted date/time with fractional seconds suffix
*/
std::string DateTime::format_fractional(char fmt[]) {
  std::string formatted = format(fmt);
  double timestamp = unix_timestamp();
  double intpart = 1.0;
  std::string fractional = std::to_string(modf(timestamp, &intpart));
  fractional = fractional.substr(fractional.find("."), fractional.size());
  return formatted + fractional;
}

/*
Format date as ISO 8601

@returns (std::string) Date/time formatted using ISO 8601 standard
*/
std::string DateTime::to_iso() { return format_fractional("%Y-%m-%dT%H:%M:%S"); }

/*
DateTime operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream &out, DateTime& dt) {
  out << "[DateTime] { Seconds since J2000: " << dt.seconds_since_j2000 
   << ", ISO: " << dt.to_iso() << " " << time_scale_str(dt.scale) << " }";
  return out;
}