#ifndef CARTESIAN_H
#define CARTESIAN_H
#include <celestial.h>
#include <vectors.h>
#include <utctime.h>

// Generic cartesian coordinates
class Cartesian {
    public:
        // Central body of the orbit these elements represent
        CelestialBody central_body;
        // Epoch at which this state is valid
        UTCTime epoch;
        // Position of the state in meters
        Vector3 position;
        // Velocity of the state in meters per second
        Vector3 velocity;

    // Default constructor
    Cartesian();

    // Direct constructor
    Cartesian(CelestialBody body, UTCTime epoch, Vector3 pos, Vector3 vel);

    // Print to std::cout
    void print();
};

// Cartesian state in the International Celestial Reference Frame (~J2000)
class ICRF: public Cartesian {
    public:

    // Default constructor (call base class)
    ICRF(){};

    // Direct constructor
    ICRF(CelestialBody body, UTCTime epoch, Vector3 pos, Vector3 vel) : Cartesian { body, epoch, pos, vel } {};
    
    // Print to std::cout
    void print();
};

#endif