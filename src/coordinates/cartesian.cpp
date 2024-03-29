#include <cartesian.h>
#include <keplerian.h>

#include <iostream>

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
Cartesian::Cartesian(CelestialBody& body, DateTime& epoch, Vector3& pos,
  Vector3& vel) {
  this->central_body = body;
  this->epoch = epoch;
  this->position = pos;
  this->velocity = vel;
}

// Constructor from KeplerianElements
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