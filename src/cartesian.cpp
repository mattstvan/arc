#include <cartesian.h>
#include <keplerian.h>

/*
Cartesian base class methods
*/

// Default constructor
Cartesian::Cartesian() {
  this->central_body = SUN;
  this->epoch = DateTime{};
  this->position = Vector3{};
  this->velocity = Vector3{};
}

// Direct constructor
Cartesian::Cartesian(CelestialBody &body, DateTime &epoch, Vector3 &pos,
                     Vector3 &vel) {
  this->central_body = body;
  this->epoch = epoch;
  this->position = pos;
  this->velocity = vel;
}

// Print to std::cout
void Cartesian::print() {
  std::cout << "[Cartesian]" << std::endl;
  std::cout << " Central Body: ";
  central_body.print();
  std::cout << " Epoch: ";
  epoch.print();
  std::cout << " Position: ";
  position.print();
  std::cout << " Velocity: ";
  velocity.print();
}

// Constructor from KeplerianElements
Cartesian::Cartesian(KeplerianElements &el) {
  this->central_body = el.central_body;
  this->epoch = el.epoch;
  // Compute PQW Position vector
  Vector3 r_pqw = Vector3{cos(el.v), sin(el.v), 0.0}.scale(
      (el.a * (1.0 - pow(el.e, 2.0))) / (1.0 + el.e * cos(el.v)));
  // Compute PQW Velocity vector
  Vector3 v_pqw = Vector3{sin(-el.v), el.e + cos(el.v), 0.0}.scale(
      sqrt(el.central_body.mu / (el.a * pow(1.0 - el.e, 2.0))));
  // Rotate PQW Position
  Vector3 r_final = r_pqw.rot_z(-el.w).rot_x(-el.i).rot_z(-el.o);
  // Rotate PQW Velocity
  Vector3 v_final = v_pqw.rot_z(-el.w).rot_x(-el.i).rot_z(-el.o);
  // Set final position/velocity
  this->position = r_final;
  this->velocity = v_final;
}

/*
ICRF class methods
*/

// Default constructor (call base class)
ICRF::ICRF(){};

// Direct constructor
ICRF::ICRF(CelestialBody &body, DateTime &epoch, Vector3 &pos, Vector3 &vel)
    : Cartesian{body, epoch, pos, vel} {};

// Constructor from KeplerianElements
ICRF::ICRF(KeplerianElements &el) : Cartesian{el} {};

// Print to std::cout
void ICRF::print() {
  std::cout << "[ICRF]" << std::endl;
  std::cout << " Central Body: ";
  central_body.print();
  std::cout << " Epoch: ";
  epoch.print();
  std::cout << " Position: ";
  position.print();
  std::cout << " Velocity: ";
  velocity.print();
}

// Convert position/velocity vectors into the sun-centered ICRF frame
ICRF ICRF::to_solar() {
  // If this state is not already heliocentric
  if (central_body.id != 10) {
    // This call will be recursive until we find a solar state
    ICRF body_icrf = central_body.propagate(epoch).to_solar();
    // Add the body's heliocentric state to this state and return
    Vector3 solar_pos = body_icrf.position.add(position);
    Vector3 solar_vel = body_icrf.velocity.add(velocity);
    return ICRF{SUN, epoch, solar_pos, solar_vel};
  } else {
    // If this state is already heliocentric, return a copy
    return ICRF{central_body, epoch, position, velocity};
  }
}

// Convert position/velocity vectors into the ICRF frame centered around another
// celestial body's position
ICRF ICRF::change_central_body(CelestialBody &body) {
  // If the requested body does differ
  if (central_body.id != body.id) {
    // If the requested body is the Sun
    if (body.id == 10) {
      return to_solar();
    }
    // Get both states in heliocentric ICRF
    ICRF body_icrf = body.propagate(epoch).to_solar();
    ICRF solar_icrf = to_solar();
    // Change the origin of this position and velocity to the other body
    Vector3 new_pos = solar_icrf.position.change_origin(body_icrf.position);
    Vector3 new_vel = solar_icrf.velocity.change_origin(body_icrf.velocity);
    // Return the new ICRF state
    return ICRF{body, epoch, new_pos, new_vel};
  } else {
    // If this state's central body is already the one requested, return a copy

    return ICRF{central_body, epoch, position, velocity};
  }
}