#ifndef DRAG_H
#define DRAG_H
#include <icrf.h>
#include <vectors.h>
#include <celestial.h>

enum DensityModel {
    // 1976 Standard Atmosphere
    Standard1976,
    // Harris-Priester model
    HarrisPriester
};

/*
Atmospheric drag model
*/
class DragModel {
public:
    // Body atmosphere this model represents
    CelestialBody central_body;
    // Density model
    DensityModel density_model;
    // Spacecraft mass
    double mass;
    // Spacecraft area
    double area;
    // Spacecraft drag coefficient
    double cd;

    // Default constructor
    DragModel();

    // Direct constructor
    DragModel(CelestialBody body, DensityModel model, double mass, double area, double cd);

    /*
    Obtain the calculated atmospheric density from the model

    @param sc_state Spacecraft inertial state
    */
    double get_density(ICRF& sc_state);

    /*
    Calculate the acceleration due to drag

    @param sc_state Spacecraft inertial state
    */
    Vector3 acceleration(ICRF& sc_state);
};

#endif