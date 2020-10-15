#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H
#include <vectors.h>
#include <cartesian.h>

// Acceleration force model
class ForceModel {
public:
  // Get acceleration force at a given state
  // This base method should be overloaded by derived classes
  virtual Vector3 acceleration(ICRF) {
    return Vector3{};
  };
};

#endif