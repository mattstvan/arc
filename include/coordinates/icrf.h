#ifndef ICRF_H
#define ICRF_H
#include <cartesian.h>

// Forward declaration
class ITRF;

// Cartesian state in the International Celestial Reference Frame (~J2000)
class ICRF : public Cartesian {
public:
  // Default constructor (call base class)
  ICRF();

  // Direct constructor
  ICRF(CelestialBody &body, DateTime &epoch, Vector3 &pos, Vector3 &vel);

  // Constructor from ITRF
  ICRF(ITRF &fixed);

  // Constructor from KeplerianElements
  ICRF(KeplerianElements &el);

  // Convert position/velocity vectors into the sun-centered ICRF frame
  ICRF to_solar();

  // Convert position/velocity vectors into the ICRF frame centered around another celestial body's position
  ICRF change_central_body(CelestialBody &body);
};

// I/O stream 
std::ostream& operator << (std::ostream &out, ICRF& icrf);

#endif