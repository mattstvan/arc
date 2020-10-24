#include <icrf.h>

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