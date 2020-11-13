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

  /*
  Default constructor

  Builds a Heliocentric state with an epoch of J2000
  and position/velocity at the system origin
  */
  Cartesian();

  /*
  Direct constructor

  @param body (celestial::CelestialBody) Body at the center of this coordinate
  system
  @param epoch (datetime::DateTime) epoch at which these coordinates are valid
  @param pos (vectors::Vector3) position vector of the state in meters
  @param vel (vectors::Vector3) velocity vector of the state in meters per second
  */
  Cartesian(CelestialBody& body, DateTime& epoch, Vector3& pos, Vector3& vel);

  /*
  Constructor from KeplerianElements

  @param el (keplerian::KeplerianElements) elements from which to calculate the
  cartesian state
  */
  Cartesian(KeplerianElements& el);
};

#endif