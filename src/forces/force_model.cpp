#include <force_model.h>

/*
Base force model class methods
*/

// Default constructor
ForceModel::ForceModel() { this->gravity_models = std::vector<GravityModel>{}; }

// Minimum constructor
ForceModel::ForceModel(ICRF &state) {
  this->gravity_models =
      std::vector<GravityModel>{GravityModel{state.central_body, false, 0, 0}};
  this->drag_model = DragModel{};
}

// Direct constructor
ForceModel::ForceModel(std::vector<GravityModel> gravity_models, DragModel drag_model) {
  this->gravity_models = gravity_models;
  this->drag_model = drag_model;
}

// Add a new GravityModel to the list
void ForceModel::add_gravity(GravityModel model) {
  // Check for existing model which matches the central body
  for (int i = 0; i < gravity_models.size(); i++) {
    // If the matching central body is found
    if (gravity_models[i].body.id == model.body.id) {
      // Replace it in place with the new model
      gravity_models[i] = model;
      // Exit the function to avoid adding it a second time
      return;
    }
  }
  // If the GravityModel is not already included, push it into the list
  gravity_models.push_back(model);
}

// Add a new GravityModel to the list
Vector3 ForceModel::acceleration(ICRF &state) {
  Vector3 acceleration, temp_accel;
  // Add gravity accelerations
  for (GravityModel gm : gravity_models) {
    temp_accel = gm.acceleration(state);
    acceleration = acceleration.add(temp_accel);
  }
  // Add drag acceleration
  temp_accel = drag_model.acceleration(state);
  acceleration = acceleration.add(temp_accel);
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