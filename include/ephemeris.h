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
Ephemeris parsing functions 
*/

/*
Parse ephemeris from STK format
@param lines Reference to vector of strings determined to represent an STK formatted ephemeris
@param ephem Reference to new Ephemeris instance to use when parsing states
*/
void parse_stk(std::vector<std::string> &lines, Ephemeris &ephem);

// Table of astronomical positions/velocities
class Ephemeris {
public:
  // Vector of ICRF states comprising the Ephemeris
  std::vector<ICRF> states;
  // Epoch of the ephemeris
  DateTime epoch;
  // Celestial body origin of the ICRF states
  CelestialBody central_body;

  // Default constructor
  Ephemeris();

  // Direct constructor
  Ephemeris(std::vector<ICRF> &states);

  // Constructor using file path
  Ephemeris(char filepath[]);

  // Use Keplerian estimation to obtain an interpolated ICRF
  // state using the nearest ICRF value contained in the ephemeris
  ICRF interpolate(DateTime &requested);

  // Create ASCII ephemeris in STK format
  std::vector<std::string> format_stk();

  // Write ephemeris to file using STK format
  void write_stk(char filename[]);
};

// I/O stream 
std::ostream& operator << (std::ostream &out, Ephemeris& eph);

#endif