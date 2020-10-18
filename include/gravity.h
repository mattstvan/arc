#ifndef GRAVITY_H
#define GRAVITY_H
#include <cartesian.h>
#include <celestial.h>
#include <vectors.h>

// Gravity model
class GravityModel {
  // Calculate acceleration due to gravity, assuming a spherical body
  Vector3 spherical(ICRF sc_state);

  // Calculate the aspherical components of acceleration due to gravity
  Vector3 aspherical(ICRF sc_state);

 public:
  // Body this model represents
  CelestialBody body;
  // Flag to determine if this model should include aspherical effects
  bool is_aspherical;
  // Geopotential degree
  int order;
  // Geopotential order
  int degree;

  // Default constructor
  GravityModel();

  // Direct constructor
  GravityModel(CelestialBody body, bool is_aspherical, int degree, int order);

  // Print to stdout
  void print();

  // Calculate acceleration on a spacecraft due to gravity, given its ICRF state
  Vector3 acceleration(ICRF state);
};

#endif