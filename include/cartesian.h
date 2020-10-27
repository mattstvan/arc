#ifndef CARTESIAN_H
#define CARTESIAN_H
#include <celestial.h>
#include <datetime.h>
#include <vectors.h>

// Forward declaration
class KeplerianElements;

/*
Generic Cartesian coordinates base class

This type is the base for ICRF, ITRF, and other cartesian coordinate system states
*/
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

  Cartesian();

  Cartesian(CelestialBody& body, DateTime& epoch, Vector3& pos, Vector3& vel);

  Cartesian(KeplerianElements& el);

  void print();
};

#endif