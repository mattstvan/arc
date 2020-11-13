#ifndef BODY_PROPAGATION_H
#define BODY_PROPAGATION_H
#include <ephemeris.h>
#include <icrf.h>
#include <datetime.h>

/*
Celestial body propagation handler

Handles reading/parsing/evaluating planetary ephemerides/position data
*/
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

  /*
  Returns a planetary ephemeris file, loading it from disk if necessary

  @param id NAIF id of the requested celestial body
  @returns ephemeris::Ephemeris instance of the requested celestial body
  @throws exceptions::ArcException if ephemeris file is not found
  */
  Ephemeris& get_ephem(int id);

public:

  // Default constructor
  BodyPropagationHandler();

  /*
  Get the state of a given CelestialBody given its NAIF ID

  @param id NAIF id of the requested celestial body
  @param epoch Requested time to which to compute an ICRF state
  @returns icrf::ICRF instance representing requested body at requested time
  @throws exceptions::ArcException if ephemeris file is not found or propagation
  fails
  */
  ICRF get_state(int id, DateTime& epoch);
};

/*
Static (singleton) celestial body propagation handler instance

Reasonably accurate propagation of celestial bodies usually require reading
large data files and evaluating their contents. A singleton ensures these files
are only read once per execution, reducing I/O latency per propagation request
*/
static BodyPropagationHandler BODY_PROPAGATOR{};

#endif