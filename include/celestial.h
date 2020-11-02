#ifndef CELESTIAL_H
#define CELESTIAL_H
#include <datetime.h>
#include <vectors.h>

#include <iostream>
#include <string>

// Forward declaration
class ICRF;

/*
Celestial body type

Handles identification and physical attributes 
(GM, radius, etc.) of celestial bodies
*/
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

    /*
    Get the body's common name

    @returns (std::string) Common name of this body
    */
    std::string get_name();

    /*
    Return the ratio between this body's polar and equatorial radii, calculated as 1
    - (r_p/r_e)

    @returns (double) Flattening ratio of this body
    */
    double flattening_ratio();

    /*
    Obtain the ICRF state of this body at an epoch

    @param epoch The requested time at which to obtain the ICRF state
    @returns (icrf::ICRF) The calculated state at the requested epoch
    */
    ICRF propagate(DateTime& epoch);
};

// I/O stream 
std::ostream& operator << (std::ostream &out, CelestialBody& body);

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
};

// Mercury definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody MERCURY = CelestialBody{
    199,
    22032000000000.0,
    2439700.0,
    2439700.0,
};

// Venus definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody VENUS = CelestialBody{
    299,
    324859000000000.0,
    6051800.0,
    6051800.0,
};

// Earth definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
// - EGM-2008 (NGA)
static CelestialBody EARTH = CelestialBody{
    399,
    398600441800000.0,
    6378137.0,
    6356752.3,
};

// Luna definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody LUNA = CelestialBody{
    301,
    4904869500000.0,
    1738100.0,
    1736000.0,
};

// Mars definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody MARS = CelestialBody{
    499,
    42828370000000.0,
    3396200.0,
    3376200.0,
};

// Jupiter definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody JUPITER = CelestialBody{
    599,
    126686534900000000.0,
    71492000.0,
    66854000.0,
};

// Saturn definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody SATURN = CelestialBody{
    699,
    37931187900000000.0,
    60268000.0,
    54364000.0,
};

// Uranus definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody URANUS = CelestialBody{
    799,
    5793939900000000.0,
    25559000.0,
    24973000.0,
};

// Neptune definition using parameters derived from:
// - NASA Space Science Data Coordinated Archive
static CelestialBody NEPTUNE = CelestialBody{
    899,
    6836529900000000.0,
    24764000.0,
    24341000.0,
};

/*
Get the common name of a body by NAIF ID

@param id NAIF ID number of the body
@returns (std::string) Common name of the given body
@throws exceptions::ArcException if ID is not known
*/
std::string get_body_name(int id);

/*
Get the CelestialBody static instance given its common name (i.e. "Mars")

@param name The common name of the requested body
@returns The static instance of the requested body
@throws exceptions::ArcException if name is not known
*/
CelestialBody get_body_by_name(std::string name);

#endif