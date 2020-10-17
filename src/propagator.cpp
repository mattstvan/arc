#include <propagator.h>
#include <ephemeris.h>
#include <gravity.h>

/*
Base Propagator methods
*/

// Return standard ICRF (this function overloaded by the derived class)
ICRF Propagator::propagate(UTCTime epoch) { return ICRF{}; }

// Create an Ephemeris by propagating over an interval
Ephemeris Propagator::step(UTCTime start, UTCTime stop, double step) {
  UTCTime t = start;
  std::vector<ICRF> states{};
  while (stop.difference(t) >= 0.0) {
    states.push_back(propagate(t));
    t = t.increment(step);
  };
  return Ephemeris{ states };
}

/*
Numerical propagator methods
*/

NumericalPropagator::NumericalPropagator(ICRF initial_state) {
  this->initial_state = initial_state;
  this->cache_state = initial_state;
  this->step_size = 60.0;
  this->forces = std::vector<ForceModel>{ GravityModel{initial_state.central_body, false, 0, 0} };
}

// Direct constructor (full settings)
NumericalPropagator::NumericalPropagator(ICRF initial_state, double step_size, std::vector<ForceModel> forces) {
  this->initial_state = initial_state;
  this->cache_state = initial_state;
  this->step_size = step_size;
  this->forces = forces;
}

// Calculate partial derivatives for numerical integration
Vector6 NumericalPropagator::derivatives(ICRF state, double h, Vector6 k=Vector6{}) {
  // Advance the epoch to t+h
  UTCTime new_epoch = state.epoch.increment(h);
  // Combine the position/velocity into a six-dimensional vector and add any k-argument
  Vector6 pos_vel = Vector6{state.position, state.velocity}.add(k);
  // Build the state to use for ForceModel evaluations
  std::array<Vector3, 2> vectors = pos_vel.split();
  ICRF sample_state {state.central_body, new_epoch, vectors[0], vectors[1]};
  // Create an empty acceleration vector
  Vector3 acceleration;
  // Iterate over the ForceModel instances, adding all accelerations at the sample state
  for (ForceModel model : forces) {
    acceleration = acceleration.add(model.acceleration(sample_state));
  }
  // Return the first-order derivative of the combined position/velocity vector (velocity/acceleration vector)
  return Vector6 {sample_state.velocity, acceleration};
}

// Propagate the inital state to specified epoch
ICRF NumericalPropagator::propagate(UTCTime epoch) {
  // Do this until the requested epoch has been reached
  while (epoch.equals(cache_state.epoch) != true) {
    // Get the difference between the requested epoch and the cached epoch
    double delta = epoch.difference(cache_state.epoch);
    // Choose the smaller of the two (avoid overstepping the target epoch)
    double mag = std::min(fabs(delta), step_size);
    // Copy the sign to step in the correct direction
    double step = copysignf(mag, delta);
    // Integrate the cached ICRf state +/- the step
    cache_state = integrate(cache_state, step);
  }
  return cache_state;
}

// Step the integration a number of seconds forward/backward
ICRF NumericalPropagator::integrate(ICRF state, double step) {
  // Simple Euler step as placeholder for the base class (don't use this)
  Vector6 deriv = derivatives(state, 0.0).scale(step);
  // Combine the state with the derivative call
  Vector6 total = Vector6{state.position, state.velocity}.add(deriv);
  std::array<Vector3, 2> vectors = total.split();
  return ICRF {state.central_body, state.epoch.increment(step), vectors[0], vectors[1]};
}