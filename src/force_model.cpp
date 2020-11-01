#include <force_model.h>

/*
Base force model class methods
*/

/*
Default constructor

Set gravity_models to empty vector
*/
ForceModel::ForceModel() { this->gravity_models = std::vector<GravityModel>{}; }

/*
Minimum constructor

Adds default of spherical central-body gravity of the given state (two-body
only)

@param state ICRF state from which to determine central body
*/
ForceModel::ForceModel(ICRF &state) {
  this->gravity_models =
      std::vector<GravityModel>{GravityModel{state.central_body, false, 0, 0}};
}

/*
Direct constructor

@param gravity_models Vector of GravityModels to include
*/
ForceModel::ForceModel(std::vector<GravityModel> gravity_models) {
  this->gravity_models = gravity_models;
}

/*
Get total acceleration force at a given state

@param state ICRF state at which to determine acceleration force
@returns Estimated acceleration vector at the given state in m/s^2
*/
Vector3 ForceModel::acceleration(ICRF &state) {
  Vector3 acceleration, temp_accel;
  // Add gravity accelerations
  for (GravityModel gm : gravity_models) {
    temp_accel = gm.acceleration(state);
    acceleration = acceleration.add(temp_accel);
  }
  return acceleration;
}

/*
ForceModel operator functions
*/

// I/O stream
std::ostream &operator<<(std::ostream &out, ForceModel &fm) {
  out << "[ForceModel]" << std::endl << " Gravity models: " << std::endl;
  for (GravityModel gm : fm.gravity_models) {
    out << " - " << gm.body.get_name() << std::endl;
  }
  return out;
}