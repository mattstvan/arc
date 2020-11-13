#include <propagator.h>

// Fourth-order Runge-Kutta
class RungeKutta4 : public NumericalPropagator {
public:
    // Direct constructor (default settings)
    RungeKutta4(ICRF initial_state);

    // Direct constructor (full settings)
    RungeKutta4(ICRF initial_state, double step_size, ForceModel force_model);

    // Step the integration a number of seconds forward/backward
    ICRF integrate(ICRF &state, double step);
};