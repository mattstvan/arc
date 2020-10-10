#include <propagator.h>

/*
Base Propagator methods
*/

// Return standard ICRF (this function overloaded by the derived class)
ICRF Propagator::propagate(UTCTime epoch) {
  return ICRF{};
}

// Create a list of states by propagating over an interval
std::vector<ICRF> Propagator::step(UTCTime start, UTCTime stop, double step) {
  UTCTime t = start;
  std::vector<ICRF> states{};
  while (stop.difference(t) >= 0.0) {
    states.push_back(propagate(t));
    t = t.increment(step);
  };
  return states;
}