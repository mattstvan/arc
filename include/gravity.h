#ifndef GRAVITY_H
#define GRAVITY_H
#include <force_model.h>
#include <celestial.h>
#include <cartesian.h>
#include <vectors.h>

// Gravity model
class GravityModel : public ForceModel {
 public:
  // Body this model represents
  CelestialBody body;
  // Flag to determine if this model should include aspherical effects
  bool aspherical;
};

#endif