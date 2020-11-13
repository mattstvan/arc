#include <gravity.h>

/*
Gravity model functions
*/

/*
Default constructor

Sets central body to Earth with aspherical effects disabled
*/
GravityModel::GravityModel() {
  this->body = EARTH;
  this->is_aspherical = false;
  this->degree = 0;
  this->order = 0;
}

/*
Direct constructor

@param body Central body of this gravity source
@param is_aspherical If aspherical gravity should be modeled
@param degree Geopotential model degree
@param order Geopotential model order
*/
GravityModel::GravityModel(CelestialBody &body, bool is_aspherical, int degree,
                           int order) {
  this->body = body;
  this->is_aspherical = is_aspherical;
  this->degree = degree;
  this->order = order;
}

/*
Calculate acceleration due to gravity, assuming a spherical body

@param sc_state Spacecraft ICRF state at which to calculate body gravity
@returns Vector of acceleration due to spherical gravity given state, in m/s^2
*/
Vector3 GravityModel::spherical(ICRF &sc_state) {
  // If we are modelling central body gravity
  if (sc_state.central_body.id == body.id) {
    return sc_state.position.scale(-body.mu / pow(sc_state.position.mag(), 3));
  } else {
    // Get the position of the body at the spacecraft state's epoch,
    // centered around the body the spacecraft is orbiting
    ICRF body_state = body.propagate(sc_state.epoch)
                          .change_central_body(sc_state.central_body);
    Vector3 spacecraft_centered_pos =
        body_state.position.change_origin(sc_state.position);
    double a_den = pow(spacecraft_centered_pos.mag(), 3.0);
    double b_den = pow(body_state.position.mag(), 3.0);
    // If this is central body gravity, b_den will be zero, causing a
    // singularity
    if (b_den == 0.0) {
      b_den = 1.0;
    }
    Vector3 b = body_state.position.scale(-1.0 / b_den);
    Vector3 grav_vector = spacecraft_centered_pos.scale(1.0 / a_den).add(b);
    return grav_vector.scale(body.mu);
  }
}

/*
Calculate the aspherical components of acceleration due to gravity

@param sc_state Spacecraft ICRF state at which to calculate body gravity
@returns Vector of acceleration due to spherical gravity at given state, in
m/s^2
*/
Vector3 GravityModel::aspherical(ICRF &sc_state) {
  // Placeholder
  return Vector3{};
}

/*
Calculate acceleration on a spacecraft due to gravity, given its ICRF state

@param sc_state Spacecraft ICRF state at which to calculate body gravity
@returns Vector of total acceleration due to gravity at given state, in m/s^2
*/
Vector3 GravityModel::acceleration(ICRF &state) {
  // Empty acceleration vector
  Vector3 accel;
  // Get spherical gravity
  Vector3 sph_grav = spherical(state);
  accel = accel.add(sph_grav);
  // If we are modeling aspherical effects
  if (is_aspherical) {
    Vector3 aspher = aspherical(state);
    accel = accel.add(aspher);
  }
  return accel;
}

/*
GravityModel operator functions
*/

// I/O stream
std::ostream &operator<<(std::ostream &out, GravityModel &gm) {
  out << "[GravityModel]" << std::endl
      << " Body: " << gm.body << std::endl
      << " Aspherical: " << gm.is_aspherical << std::endl
      << " Geopotential Degree/Order: " << gm.degree << "/" << gm.order;
  return out;
}