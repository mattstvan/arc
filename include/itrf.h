#ifndef ITRF_H
#define ITRF_H
#include <icrf.h>

// Cartesian state in the International Celestial Reference Frame (~J2000)
class ITRF : public Cartesian {
public:
  // Default constructor (call base class)
  ITRF();

  // Direct constructor
  ITRF(CelestialBody &body, DateTime &epoch, Vector3 &pos, Vector3 &vel);

  // Constructor from ICRF
  ITRF(ICRF &inertial);

  // Print to std::cout
  void print();
};

#endif