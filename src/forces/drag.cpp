#include <drag.h>

#include <cmath>

// 1976 Standard Exponential atmosphere values
double std1976_values[28][3] = {
  {0, 1.225, 7.249e+3},
  {25000, 3.899e-2, 6.349e+3},
  {30000, 1.774e-2, 6.682e+3},
  {40000, 3.972e-3, 7.554e+3},
  {50000, 1.057e-3, 8.382e+3},
  {60000, 3.206e-4, 7.714e+3},
  {70000, 8.77e-5, 6.549e+3},
  {80000, 1.905e-5, 5.799e+3},
  {90000, 3.396e-6, 5.382e+3},
  {100000, 5.297e-7, 5.877e+3},
  {110000, 9.661e-8, 7.263e+3},
  {120000, 2.438e-8, 9.473e+3},
  {130000, 8.484e-9, 12.636e+3},
  {140000, 3.845e-9, 16.149e+3},
  {150000, 2.07e-9, 22.523e+3},
  {180000, 5.464e-10, 29.74e+3},
  {200000, 2.789e-10, 37.105e+3},
  {250000, 7.248e-11, 45.546e+3},
  {300000, 2.418e-11, 53.628e+3},
  {350000, 9.518e-12, 53.298e+3},
  {400000, 3.725e-12, 58.515e+3},
  {450000, 1.585e-12, 60.828e+3},
  {500000, 6.967e-13, 63.822e+3},
  {600000, 1.454e-13, 71.835e+3},
  {700000, 3.614e-14, 88.667e+3},
  {800000, 1.17e-14, 124.64e+3},
  {900000, 5.245e-15, 181.05e+3},
  {1000000, 3.019e-15, 268.0e+3}
};

// Standard 1976 Atmosphere density
double density_std1976(ICRF& sc_state) {
    // Approximate altitude at this position
    double alt = sc_state.position.mag() - EARTH.radius_equator;
    // Values to use in the density calculation
    double *values = std1976_values[0];
    // If altitude is greater than the last available value
    if (alt >= std1976_values[27][0]) {
        values = std1976_values[27];
    } else {
        // Search to find the two density values between which the altitude lies
        for (int i = 0; i < 27; i++) {
            if (std1976_values[i][0] <= alt && alt < std1976_values[i+1][0]) {
                values = std1976_values[i];
            }
        }
    }
    // values[0]: Base altitude
    // values[1]: Density (kg/m^3)
    // values[2]: Scale height
    return values[1] * exp(-(alt - values[0]) / values[2]);
}

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
    if (density_model == Standard1976) {
        return density_std1976(sc_state);
    } else {
        return 0;
    }
}

// Calculate the acceleration due to drag
Vector3 DragModel::acceleration(ICRF& sc_state) {
    // Get atmospheric density in kg/m^3
    double dens = get_density(sc_state);
    // Include body's rotation in relative velocity
    Vector3 v_rel_a = central_body.rotation.inverse().cross(sc_state.position);
    Vector3 v_rel = sc_state.velocity.add(v_rel_a);
    // Magnitude of the drag force 
    double f_mag = 0.5 * dens * ((cd * area) / mass) * pow(v_rel.mag(), 2);
    // The acceleration vector of the drag force in m/s^2
    // This is the inverse of normalized relative velocity vector, scaled to the magnitude of the drag
    return v_rel.inverse().unit().scale(f_mag);
}