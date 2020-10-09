#include <cartesian.h>

#include <iostream>

/*
Cartesian base class methods
*/

// Default constructor
Cartesian::Cartesian() {
  this->central_body = SUN;
  this->epoch = UTCTime{};
  this->position = Vector3{};
  this->velocity = Vector3{};
}

// Direct constructor
Cartesian::Cartesian(CelestialBody body, UTCTime epoch, Vector3 pos,
                     Vector3 vel) {
  this->central_body = body;
  this->epoch = epoch;
  this->position = pos;
  this->velocity = vel;
}

/*
ICRF class methods
*/

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