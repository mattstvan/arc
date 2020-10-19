#include <force_model.h>

/*
Base force model class methods
*/

// Default constructor
ForceModel::ForceModel() {
  this->gravity_models = std::vector<GravityModel> {};
}

// Direct constructor
ForceModel::ForceModel(std::vector<GravityModel> &gravity_models) {
  this->gravity_models = gravity_models;
}

// Get total acceleration force at a given state
Vector3 ForceModel::acceleration(ICRF &state) {
  Vector3 acceleration;
  // Add gravity accelerations
  for (GravityModel gm : gravity_models) {
    acceleration = acceleration.add(gm.acceleration(state));
  }
  return acceleration;
}