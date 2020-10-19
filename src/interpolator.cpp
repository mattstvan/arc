#include <interpolator.h>

/*
Interpolator propagator methods
*/

// Direct constructor
InterpolatorPropagator::InterpolatorPropagator(Ephemeris &ephemeris) {
  this->ephemeris = ephemeris;
}

// Propagate to the requested state using the nearest ICRF value contained in
// the ephemeris
ICRF InterpolatorPropagator::propagate(UTCTime &epoch) {
  return ephemeris.interpolate(epoch);
}