#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H
#include <icrf.h>
#include <vectors.h>
#include <gravity.h>
#include <vector>

// Acceleration force model
class ForceModel {
  // Gravity sources to model
  std::vector<GravityModel> gravity_models;
 public:
  // Default constructor
  ForceModel();

  // Minimum constructor
  ForceModel(ICRF &state);

  // Direct constructor
  ForceModel(std::vector<GravityModel> gravity_models);

  // Add a new GravityModel to the list
  void add_gravity(GravityModel model);

  // Get total acceleration force at a given state
  Vector3 acceleration(ICRF &state);
};

#endif