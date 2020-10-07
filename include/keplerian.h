#ifndef KEPLERIAN_H
#define KEPLERIAN_H
#include <celestial.h>
#include <utctime.h>
#include <cartesian.h>

// Keplerian elements orbital elements
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
    KeplerianElements(CelestialBody body, UTCTime epoch, double a, double e, double i, double o, double w, double v);

    // Constructor using Cartesian instance
    KeplerianElements(Cartesian& vector);
};

#endif