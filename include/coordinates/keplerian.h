#ifndef KEPLERIAN_H
#define KEPLERIAN_H
#include <celestial.h>
#include <datetime.h>
#include <propagator.h>

#include <iostream>

// Forward declaration
class Cartesian;

// Keplerian orbital elements
class KeplerianElements {
 public:
  // Central body of the orbit these elements represent
  CelestialBody central_body;
  // Time at which the elements are correct
  DateTime epoch;
  // Semi-Major axis in meters
  double a;
  // Eccentricity (unitless)
  double e;
  // Inclination (radians)
  double i;
  // Right Ascension of Ascending Node (radians)
  double o;
  // Argument of Periapsis (radians)
  double w;
  // True Anomaly (radians)
  double v;

  // Default constructor
  KeplerianElements();

  // Direct constructor
  KeplerianElements(CelestialBody &body, DateTime epoch, double a, double e,
                    double i, double o, double w, double v);

  // Constructor using Cartesian instance
  KeplerianElements(Cartesian &vector);

  // Print to std::cout
  void print();

  // Compute mean motion
  double mean_motion();

  // Propagate the True Anomaly of the elements to a specified epoch
  KeplerianElements propagate_to(DateTime &t);
};

// Propagator using Kepler's method
class KeplerianPropagator : public Propagator {
 public:
  // Initial KeplerianElements state
  KeplerianElements initial_state;

  // Direct constructor
  KeplerianPropagator(KeplerianElements state);

  // Propagate the inital state to specified epoch
  ICRF propagate(DateTime &epoch);
};

#endif