#ifndef CELESTIAL_H
#define CELESTIAL_H
#include <utctime.h>
#include <vectors.h>

#include <iostream>
#include <string>

// Forward declaration
class ICRF;

// Celestial body
class CelestialBody {
 public:
  // NAIF ID Code
  int id;
  // GM in m^3/s^2
  double mu;
  // Equatorial radius in meters
  double radius_equator;
  // Polar radius in meters
  double radius_polar;
  // Flattening ratio
  double flattening;
  // Rotation vector in rad/s
  Vector3 rotation;

  // Print to std::cout
  void print();

  // Return the common name of the body as a String
  std::string get_name();

  // Return the ICRF state of the body at an epoch
  ICRF propagate(UTCTime epoch);
};

// Sun definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody SUN = CelestialBody{
    10,
    132712440018000003072.0,
    69570000000.0,
    69570000000.0,
    0.0,
    Vector3{0.0, 0.0, 2.8653290845717256e-6},
};

// Earth definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
// - EGM-2008 (NGA)
// - WGS-84 (NIMA 1997)
static CelestialBody EARTH = CelestialBody{
    399,
    398600441800000.0,
    6378137.0,
    6356752.3,
    0.0033528106647474805,
    Vector3{0.0, 0.0, 7.2921158553e-5},
};

#endif