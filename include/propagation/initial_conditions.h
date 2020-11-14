#ifndef INITIAL_CONDITIONS_H
#define INITIAL_CONDITIONS_H
#include <icrf.h>
#include <datetime.h>

/*
Spacecraft propagation initial conditions

States, settings, and conditions which define the
propagation run to perform
*/
class InitialConditions {
 public:
  // Initial state to propagate
  ICRF initial_state;

  /*
  Default constructor
  */
  InitialConditions();

  /*
  Default direct constructor

  Assumes default propagation settings:
  - Two-body gravity only
  - Runge-Kutta 4 integrator
  - 60 second step size (integration and propagation)

  @param initial_state Initial state to propagate
  @param start Start time of desired propagation interval
  @param stop Stop time of desired propagation interval
  */
  InitialConditions(ICRF initial_state, DateTime start, DateTime stop);
};

#endif