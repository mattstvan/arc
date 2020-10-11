#ifndef BODY_PROPAGATOR_H
#define BODY_PROPAGATOR_H
#include <ephemeris.h>
#include <cartesian.h>
#include <utctime.h>

// CelestialBody propagation handler
class BodyPropagationHandler {
 // Mercury states
 Ephemeris mercury;
 // Venus states
 Ephemeris venus;
 // Earth states
 Ephemeris earth;
 // Luna (moon) states
 Ephemeris luna;
 // Mars states
 Ephemeris mars;
 // Jupiter states
 Ephemeris jupiter;
 // Saturn states
 Ephemeris saturn;
 // Uranus states
 Ephemeris uranus;
 // Neptune states
 Ephemeris neptune;

 public:
  // Default constructor
  BodyPropagationHandler();
  
  // Get the state of a given CelestialBody given its NAIF ID
  ICRF get_state(int id, UTCTime);
};

#endif