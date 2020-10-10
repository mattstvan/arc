#ifndef EPHEMERIS_H
#define EPHEMERIS_H
#include <vector>
#include <string>
#include <cartesian.h>
#include <utctime.h>
#include <celestial.h>

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
  Ephemeris(std::vector<ICRF> states, UTCTime epoch, CelestialBody body);

  // Print to std::cout
  void print();

  // Create ASCII ephemeris in STK format
  std::vector<std::string> format_stk();
};

#endif