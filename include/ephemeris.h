#ifndef EPHEMERIS_H
#define EPHEMERIS_H
#include <propagator.h>
#include <cartesian.h>
#include <celestial.h>
#include <utctime.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Table of astronomical positions/velocities
class Ephemeris {
 public:
  // Vector of ICRF states comprising the Ephemeris
  std::vector<ICRF> states;
  // Epoch of the ephemeris
  UTCTime epoch;
  // Celestial body origin of the ICRF states
  CelestialBody central_body;

  // Default constructor
  Ephemeris();

  // Direct constructor
  Ephemeris(std::vector<ICRF> states);

  // Print to std::cout
  void print();

  // Use Keplerian estimation to obtain an interpolated ICRF
  // state using the nearest ICRF value contained in the ephemeris
  ICRF interpolate(UTCTime requested);

  // Create ASCII ephemeris in STK format
  std::vector<std::string> format_stk();

  // Write ephemeris to file using STK format
  void write_stk(char filename[]);
};

#endif