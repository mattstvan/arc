#ifndef CARTESIAN_H
#define CARTESIAN_H
#include <celestial.h>
#include <datetime.h>
#include <vectors.h>

#include <iostream>

// Forward declaration
class KeplerianElements;

// Generic cartesian coordinates
class Cartesian {
public:
  // Central body of the orbit these elements represent
  CelestialBody central_body;
  // Epoch at which this state is valid
  DateTime epoch;
  // Position of the state in meters
  Vector3 position;
  // Velocity of the state in meters per second
  Vector3 velocity;

  // Default constructor
  Cartesian();

  // Direct constructor
  Cartesian(CelestialBody &body, DateTime &epoch, Vector3 &pos, Vector3 &vel);

  // Constructor from KeplerianElements
  Cartesian(KeplerianElements &el);

  // Print to std::cout
  void print();
};

#endif