#include <propagator.h>
#include <ephemeris.h>
#include <gravity.h>

/*
Base Propagator methods
*/

// Return standard ICRF (this function overloaded by the derived class)
ICRF Propagator::propagate(UTCTime &epoch) { return ICRF{}; }

// Create an Ephemeris by propagating over an interval
Ephemeris Propagator::step(UTCTime &start, UTCTime &stop, double step) {
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
  this->step_size = 15.0;
  GravityModel central_grav {initial_state.central_body, false, 0, 0};
  this->force_model = ForceModel {std::vector<GravityModel> {central_grav}};
}

// Direct constructor (full settings)
NumericalPropagator::NumericalPropagator(ICRF initial_state, double step_size, ForceModel force_model) {
  this->initial_state = initial_state;
  this->cache_state = initial_state;
  this->step_size = step_size;
  this->force_model = force_model;
}

// Calculate partial derivatives for numerical integration
Vector6 NumericalPropagator::derivatives(ICRF &state, double h, Vector6 k) {
  // Advance the epoch to t+h
  UTCTime new_epoch = state.epoch.increment(h);
  // Combine the position/velocity into a six-dimensional vector and add any k-argument
  Vector6 pos_vel = Vector6{state.position, state.velocity}.add(k);
  // Build the state to use for ForceModel evaluations
  std::array<Vector3, 2> vectors = pos_vel.split();
  ICRF sample_state {state.central_body, new_epoch, vectors[0], vectors[1]};
  // Create acceleration vector
  Vector3 acceleration = force_model.acceleration(sample_state);
  // Return the first-order derivative of the combined position/velocity vector (velocity/acceleration vector)
  Vector6 final {sample_state.velocity, acceleration};
  return final;
}

// Propagate the inital state to specified epoch
ICRF NumericalPropagator::propagate(UTCTime &epoch) {
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
ICRF NumericalPropagator::integrate(ICRF &state, double step) { return state; }