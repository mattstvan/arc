#include <drag.h>

// Default constructor
DragModel::DragModel() {
    this->central_body = EARTH;
    this->density_model = Standard1976;
    this->mass = 1000;
    this->area = 4;
    this->cd = 1.2;
}

// Direct constructor
DragModel::DragModel(CelestialBody body, DensityModel model, double mass, double area, double cd) {
    this->central_body = body;
    this->density_model = model;
    this->mass = mass;
    this->area = area;
    this->cd = cd;
}

// Obtain the calculated atmospheric density from the selected density model
double DragModel::get_density(ICRF& sc_state) {
    return 0.0;
}

// Calculate the acceleration due to drag
Vector3 DragModel::acceleration(ICRF& sc_state) {
    return Vector3 {};
}