#ifndef INITIAL_CONDITIONS_H
#define INITIAL_CONDITIONS_H
#include <datetime.h>
#include <icrf.h>
#include <propagator.h>

/*
Spacecraft propagation initial conditions

States, settings, and conditions which define the
propagation run to perform
*/
class InitialConditions {
 public:
  // Initial state to propagate
  ICRF initial_state;
  // Propagator instance to use
  Propagator propagator;
  // Ephemeris option boolean
  bool build_ephem;
  // Ephemeris start
  DateTime ephem_start;
  // Ephemeris stop
  DateTime ephem_stop;
  // Ephemeris step size
  double ephem_step;
  // Ephemeris format
  char* ephem_fmt;
  // Ephemeris filename
  char* ephem_file;

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

  /*
  Constructor from JSON file

  Constructor initial conditions from JSON file
  @param filename Filesystem location to read
  */
  InitialConditions(const char filepath[]);
};

/*
InitialConditions operator functions
*/

// I/O stream
std::ostream &operator<<(std::ostream &out, InitialConditions &ic);

#endif