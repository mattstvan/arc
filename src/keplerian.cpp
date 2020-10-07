#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <keplerian.h>

/*
Keplerian elements methods
*/

// Default constructor
KeplerianElements::KeplerianElements() {
    this->central_body = SUN;
    this->epoch = UTCTime{};
    this->a = 0.0;
    this->e = 0.0;
    this->i = 0.0;
    this->o = 0.0;
    this->w = 0.0;
    this->v = 0.0;
}

// Direct constructor
KeplerianElements::KeplerianElements(CelestialBody body, UTCTime epoch, double a, double e, double i, double o, double w, double v) {
    this->central_body = body;
    this->epoch = epoch;
    this->a = a;
    this->e = e;
    this->i = i;
    this->o = o;
    this->w = w;
    this->v = v;
}

    // Constructor using Cartesian instance
    KeplerianElements::KeplerianElements(Cartesian& vector) {
        // Copy the central body and epoch
        this->central_body = vector.central_body;
        this->epoch = vector.epoch;
        // Calculate Semi-major axis
        double mu = vector.central_body.mu;
        double energy = pow(vector.velocity.mag(), 2.0) / 2.0 - mu / vector.position.mag();
        double a = -(mu / (2.0 * energy));
        this->a = a;
        // Calculate eccentricity vector and its magnitude (e)
        Vector3 e_vec_a = vector.position.scale(pow(vector.velocity.mag(), 2.0) - mu / vector.position.mag());
        Vector3 e_vec_b = vector.velocity.scale(vector.position.dot(vector.velocity));
        Vector3 e_vec = e_vec_a.add(e_vec_b.inverse()).scale(1.0 / mu);
        double e = e_vec.mag();
        this->e = e;
        Vector3 h = vector.position.cross(vector.velocity);
        // Inclination
        double i = acos(h.z / h.mag());
        this->i = i;
        Vector3 n = (Vector3 {0.0, 0.0, 1.0}).cross(h);
        // RAAN
        double o = acos(n.x / n.mag());
        // Argument of periapsis
        double w = acos(n.dot(e_vec) / (n.mag() * e));
        // True anomaly
        double v = acos(e_vec.dot(vector.position) / (e * vector.position.mag()));
        // Sanity check RAAN
        if (n.y < 0.0) {
            o = 2.0 * M_PI - o;
        };
        if (isnan(o)) {
            o = 0.0;
        };
        // Sanity check argument of periapsis
        if (e_vec.z < 0.0) {
            w = 2.0 * M_PI - w;
        };
        if (isnan(w)) {
            w = 0.0;
        };
        // Sanity check true anomaly
        if (vector.position.dot(vector.velocity) < 0.0) {
            v = 2.0 * M_PI - v;
        };
        if (isnan(v)) {
            v = 0.0;
        };
        // Set final variables
        this->o = o;
        this->w = w;
        this->v = v;
    }

// Print to std::cout
void KeplerianElements::print() {
    std::cout << "[KeplerianElements]" << std::endl;
    std::cout << " Central Body: ";
    central_body.print();
    std::cout << " Epoch: ";
    epoch.print();
    std::cout << " A: " << a << std::endl;
    std::cout << " E: " << e << std::endl;
    std::cout << " I: " << i * (180.0/M_PI) << std::endl;
    std::cout << " O: " << o * (180.0/M_PI) << std::endl;
    std::cout << " W: " << w * (180.0/M_PI) << std::endl;
    std::cout << " V: " << v * (180.0/M_PI) << std::endl;
}