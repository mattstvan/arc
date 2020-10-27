#include <cartesian.h>
#include <keplerian.h>

#include <iostream>

/*
Cartesian base class methods
*/

/*
Default constructor

Builds a Heliocentric state with an epoch of J2000
and position/velocity at the system origin
 */
Cartesian::Cartesian() {
  this->central_body = SUN;
  this->epoch = DateTime{};
  this->position = Vector3{};
  this->velocity = Vector3{};
}

/*
Direct constructor

@param body (celestial::CelestialBody) Body at the center of this coordinate system
@param epoch (datetime::DateTime) epoch at which these coordinates are valid
@param pos (vectors::Vector3) position vector of the state in meters
@param vel (vectors::Vector3) velocity vector of the state in meters per second
*/
Cartesian::Cartesian(CelestialBody& body, DateTime& epoch, Vector3& pos,
  Vector3& vel) {
  this->central_body = body;
  this->epoch = epoch;
  this->position = pos;
  this->velocity = vel;
}

/*
Constructor from KeplerianElements

@param el (keplerian::KeplerianElements) elements from which to calculate the cartesian state
*/
Cartesian::Cartesian(KeplerianElements& el) {
  this->central_body = el.central_body;
  this->epoch = el.epoch;
  // Compute PQW Position vector
  Vector3 r_pqw = Vector3{ cos(el.v), sin(el.v), 0.0 }.scale(
    (el.a * (1.0 - pow(el.e, 2.0))) / (1.0 + el.e * cos(el.v)));
  // Compute PQW Velocity vector
  Vector3 v_pqw = Vector3{ sin(-el.v), el.e + cos(el.v), 0.0 }.scale(
    sqrt(el.central_body.mu / (el.a * pow(1.0 - el.e, 2.0))));
  // Rotate PQW Position
  Vector3 r_final = r_pqw.rot_z(-el.w).rot_x(-el.i).rot_z(-el.o);
  // Rotate PQW Velocity
  Vector3 v_final = v_pqw.rot_z(-el.w).rot_x(-el.i).rot_z(-el.o);
  // Set final position/velocity
  this->position = r_final;
  this->velocity = v_final;
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