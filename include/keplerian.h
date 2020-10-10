#ifndef KEPLERIAN_H
#define KEPLERIAN_H
#define _USE_MATH_DEFINES
#include <celestial.h>
#include <utctime.h>

#include <cmath>
#include <iostream>

// Forward declaration
class Cartesian;

// Keplerian orbital elements
class KeplerianElements {
 public:
  // Central body of the orbit these elements represent
  CelestialBody central_body;
  // Time at which the elements are correct
  UTCTime epoch;
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
  KeplerianElements(CelestialBody body, UTCTime epoch, double a, double e,
                    double i, double o, double w, double v);

  // Constructor using Cartesian instance
  KeplerianElements(Cartesian vector);

  // Print to std::cout
  void print();

  // Compute mean motion
  double KeplerianElements::mean_motion();

  // Propagate the True Anomaly of the elements to a specified epoch
  KeplerianElements propagate_to(UTCTime t);
};

#endif