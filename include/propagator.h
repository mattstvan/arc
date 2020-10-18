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
  virtual Ephemeris step(UTCTime start, UTCTime stop, double step);
};

// Numerical propagator base class
class NumericalPropagator : public Propagator {
public:
  // State used as the initial state
  ICRF initial_state;
  // Number of seconds between integration steps
  double step_size;
  // State used for the initial condition of the next integration step
  ICRF cache_state;
  // Force model
  ForceModel force_model;

  // Direct constructor (default settings)
  NumericalPropagator(ICRF initial_state);

  // Direct constructor (full settings)
  NumericalPropagator(ICRF initial_state, double step_size, ForceModel force_model);

  // Propagate the inital state to specified epoch
  ICRF propagate(UTCTime epoch);

  // Calculate partial derivatives for numerical integration
  Vector6 derivatives(ICRF state, double h, Vector6 k);

  // Step the integration a number of seconds forward/backward
  ICRF integrate(ICRF state, double step);

};

#endif