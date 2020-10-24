#ifndef CELESTIAL_H
#define CELESTIAL_H
#include <datetime.h>
#include <vectors.h>

#include <iostream>
#include <string>

// Forward declaration
class ICRF;

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

    // Return the ICRF state of the body at an epoch
    ICRF propagate(DateTime &epoch);
};

/*
Planet definitions
*/

// Sun definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody SUN = CelestialBody{
    10,
    132712440018000003072.0,
    69570000000.0,
    69570000000.0,
    0.0,
    Vector3{0.0, 0.0, 2.8653290845717256e-6},
};

// Mercury definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody MERCURY = CelestialBody{
    199,
    22032000000000.0,
    2439700.0,
    2439700.0,
    0.0,
    Vector3{0.0, 0.0, 1.239932688259683e-06},
};

// Venus definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody VENUS = CelestialBody{
    299,
    324859000000000.0,
    6051800.0,
    6051800.0,
    0.0,
    Vector3{0.0, 0.0, 0.0},
};

// Earth definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
// - EGM-2008 (NGA)
// - WGS-84 (NIMA 1997)
static CelestialBody EARTH = CelestialBody{
    399,
    398600441800000.0,
    6378137.0,
    6356752.3,
    0.0033528106647474805,
    Vector3{0.0, 0.0, 7.2921158553e-5},
};

// Luna definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody LUNA = CelestialBody{
    301,
    4904869500000.0,
    1738100.0,
    1736000.0,
    0.001208215867901763,
    Vector3{0.0, 0.0, 0.0},
};

// Mars definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody MARS = CelestialBody{
    499,
    42828370000000.0,
    3396200.0,
    3376200.0,
    0.005888934691714254,
    Vector3{0.0, 0.0, 7.077632258808082e-05},
};

// Return the common name of a body by NAIF ID
std::string get_body_name(int id);

// Return the CelestialBody given a common name (i.e. "Mars")
CelestialBody get_body_by_name(std::string name);

#endif