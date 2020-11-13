#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#include <propagator.h>
#include <ephemeris.h>

/*
Propagator using existing Ephemeris

Interpolates ICRF states using keplerian estimation
*/
class InterpolatorPropagator : public Propagator {
public:
  // Ephemeris from which to interpolate states
  Ephemeris ephemeris;

  /*
  Direct constructor

  @param ephemeris Ephemeris instance to use for interpolation
  */
  InterpolatorPropagator(Ephemeris& ephemeris);

  /*
  Propagate to the requested time using the nearest ICRF value contained in
  the ephemeris

  @param epoch Requested time at which to obtain interpolated state
  */
  ICRF propagate(DateTime& epoch);
};

#endif