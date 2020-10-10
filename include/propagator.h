#ifndef PROPAGATOR_H
#define PROPAGATOR_H
#include <cartesian.h>
#include <utctime.h>

#include <vector>

// Base propagator class
class Propagator {
 public:
  // Propagate the inital state to specified epoch
  virtual ICRF propagate(UTCTime epoch);

  // Create a list of states by propagating over an interval
  std::vector<ICRF> step(UTCTime start, UTCTime stop, double step);
};

#endif