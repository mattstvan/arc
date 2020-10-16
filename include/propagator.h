#ifndef PROPAGATOR_H
#define PROPAGATOR_H
#include <cartesian.h>
#include <utctime.h>
#include <force_model.h>

#include <vector>

// Forward declaration
class Ephemeris;

// Base propagator class
class Propagator {
public:
  // Propagate the inital state to specified epoch
  virtual ICRF propagate(UTCTime epoch);

  // Create an Ephemeris by propagating over an interval
  Ephemeris step(UTCTime start, UTCTime stop, double step);
};

// Numerical propagator base class
class NumericalPropagator : public Propagator {
  // State used for the initial condition of the next integration step
  ICRF cache_state;
  // List of force models
  std::vector<ForceModel> forces;

public:
  // State used as the initial state
  ICRF initial_state;
  // Number of seconds between steps
  double step_size;

  // Direct constructor (default settings)
  NumericalPropagator(ICRF initial_state);

  // Propagate the inital state to specified epoch
  ICRF propagate(UTCTime epoch);
};

#endif