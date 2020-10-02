#ifndef CELESTIAL_H
#define CELESTIAL_H
#include <string>
#include <vectors.h>

// Celestial body
class CelestialBody {
    public:
        // NAIF ID Code
        int id;
        // GM in m^3/s^2
        double mu;
        // Equatorial radius in meters
        double radius_equator;
        // Polar radius in meters
        double radius_polar;
        // Flattening ratio
        double flattening;
        // Rotation vector in rad/s
        Vector3 rotation;

    // Print to std::cout
    void print();
    
    // Return the common name of the body as a String
    std::string get_name();
};

static CelestialBody SUN = CelestialBody {
    10, 
    132712440018000003072.0,
    69570000000.0,
    69570000000.0,
    0.0,
    Vector3 {0.0, 0.0, 2.8653290845717256e-06}
};

#endif