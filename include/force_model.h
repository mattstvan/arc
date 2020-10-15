#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H
#include <cartesian.h>
#include <vectors.h>

// Acceleration force model
class ForceModel {
 public:
  // Get acceleration force at a given state
  // This base method should be overloaded by derived classes
  virtual Vector3 acceleration(ICRF state) { return Vector3{}; };
};

#endif