#ifndef EPHEMERIS_H
#define EPHEMERIS_H
#include <icrf.h>
#include <keplerian.h>
#include <celestial.h>
#include <propagator.h>
#include <datetime.h>
#include <file_io.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
Standalone ephemeris file parsers
*/

/*
Parse ephemeris from STK format

@param lines Reference to vector of strings determined to represent an STK
formatted ephemeris
@param ephem Reference to new Ephemeris instance to use when parsing states
*/
void parse_stk(std::vector<std::string> &lines, Ephemeris &ephem);

/*
Table of astronomical positions/velocities

States are always stored in ICRF, centered around a single body
*/
class Ephemeris {
public:
  // Vector of ICRF states comprising the Ephemeris
  std::vector<ICRF> states;
  // Epoch of the ephemeris
  DateTime epoch;
  // Celestial body origin of the ICRF states
  CelestialBody central_body;

  /*
  Default constructor

  Creates empty list of states, sets epoch to J2000 and central body to Sun
  */
  Ephemeris();

  /*
  Direct constructor

  Construct an Ephemeris from a vector of ICRF states

  @param states ICRF states comprising the ephemeris
  */
  Ephemeris(std::vector<ICRF> &states);

  /*
  Constructor using file path

  Attempt to read in an ephemeris file
  @param filepath Ephemeris location in the filesystem
  @throws ArcException if error is encountered reading or parsing the file
  */
  Ephemeris(const char filepath[]);

  /*
  Use Keplerian estimation to obtain an interpolated ICRF
  state by using the nearest (by time) ICRF value contained in the ephemeris

  @param requested Date/time at which to estimate ICRF state
  @returns Interpolated ICRF state at the requested epoch
  */
  ICRF interpolate(DateTime &requested);

  /*
  Create ASCII ephemeris in STK format (.e)

  @returns Vector of ASCII lines comprising an STK ephemeris file
  */
  std::vector<std::string> format_stk();

  /*
  Write ephemeris to file using STK format

  @param filename File system location at which to write the new ephemeris file
  */
  void write_stk(const char filename[]);
};

// I/O stream 
std::ostream& operator << (std::ostream &out, Ephemeris& eph);

#endif