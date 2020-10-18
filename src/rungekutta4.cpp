#include <rungekutta4.h>

/*
Fourth-order Runge-Kutta methods
*/

// Direct constructor (default settings)
RungeKutta4::RungeKutta4(ICRF initial_state) : NumericalPropagator{ initial_state } {}

// Direct constructor (full settings)
RungeKutta4::RungeKutta4(ICRF initial_state, double step_size, ForceModel force_model) : NumericalPropagator{ initial_state, step_size, force_model } {}

// Propagate the inital state to specified epoch
ICRF RungeKutta4::propagate(UTCTime epoch) {
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
ICRF RungeKutta4::integrate(ICRF state, double step) {
  // Take derivatives 
  Vector6 k1 = derivatives(state, 0.0, Vector6{});
  Vector6 k2 = derivatives(state, step / 2.0, k1.scale(1.0/2.0));
  Vector6 k3 = derivatives(state, step / 2.0, k2.scale(1.0/2.0));
  Vector6 k4 = derivatives(state, step, k3);
  // Start combined vector and add weighted values
  Vector6 total = k1.add(k2.scale(2.0));
  total = total.add(k3.scale(2.0));
  total = total.add(k4).scale(step / 6.0);
  // Combined position/velocity
  Vector6 pos_vel {state.position, state.velocity};
  // Add the total weighted velocity/acceleration vector
  std::array<Vector3, 2> final_vectors = pos_vel.add(total).split();
  // Build the new state and return
  return ICRF {state.central_body, state.epoch.increment(step), final_vectors[0], final_vectors[1]};
}