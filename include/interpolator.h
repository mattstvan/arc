#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#include <propagator.h>
#include <ephemeris.h>

// Propagator using existing Ephemeris
class InterpolatorPropagator : public Propagator {
public:
  // Ephemeris from which to interpolate states
  Ephemeris ephemeris;

  // Direct constructor
  InterpolatorPropagator(Ephemeris ephemeris);

  // Propagate to the requested state using the nearest ICRF value contained in
  // the ephemeris
  ICRF propagate(UTCTime epoch);
};

#endif