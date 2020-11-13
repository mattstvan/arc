#include <rungekutta4.h>

/*
Fourth-order Runge-Kutta methods
*/

// Direct constructor (default settings)
RungeKutta4::RungeKutta4(ICRF initial_state) : NumericalPropagator{ initial_state } {}

// Direct constructor (full settings)
RungeKutta4::RungeKutta4(ICRF initial_state, double step_size, ForceModel force_model) : NumericalPropagator{ initial_state, step_size, force_model } {}

// Step the integration a number of seconds forward/backward
ICRF RungeKutta4::integrate(ICRF &state, double step) {
  // Take derivatives 
  Vector6 k0 {};
  Vector6 k1 = derivatives(state, 0.0, k0).scale(step);
  Vector6 w_k1 = k1 / 2.0;
  Vector6 k2 = derivatives(state, step / 2.0, w_k1).scale(step);
  Vector6 w_k2 = k2 / 2.0;
  Vector6 k3 = derivatives(state, step / 2.0, w_k2).scale(step);
  Vector6 k4 = derivatives(state, step, k3).scale(step);
  // Start combined vector and add weighted values
  k2 = k2 * 2;
  k3 = k3 * 2;
  Vector6 total = k1 + k2;
  total = total + k3;
  total = total + k4;
  total = total / 6;
  // Combined position/velocity
  Vector6 pos_vel {state.position, state.velocity};
  // Add the total weighted velocity/acceleration vector
  std::array<Vector3, 2> final_vectors = (pos_vel + total).split();
  // Build the new state and return
  DateTime new_epoch = state.epoch.increment(step);
  return ICRF {state.central_body, new_epoch, final_vectors[0], final_vectors[1]};
}