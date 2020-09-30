#include <iostream>
#include <cmath>
#include <vectors.h>

// Default constructor
Vector3::Vector3() {
    this->x = 1.0;
    this->y = 1.0;
    this->z = 1.0;
}

// Constructor using doubles
Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
};

// Print to std::cout
void Vector3::print() {
    std::cout << "[Vector3]" << std::endl;
    std::cout << " X: " << x << "\n Y: " << y << "\n Z: " << z << std::endl;
};

// Calculate the magnitude
double Vector3::mag() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
};

// Scale by a scalar value using element-wise multiplication
Vector3 Vector3::scale(double scalar) {
    double new_x = x * scalar;
    double new_y = y * scalar;
    double new_z = z * scalar;
    return Vector3 {new_x, new_y, new_z};
};

// Calculate the unit vector
Vector3 Vector3::unit() {
    return scale(1.0/mag());
};

// Add another Vector3 using element-wise addition
Vector3 Vector3::add(Vector3 v) {
    double new_x = x + v.x;
    double new_y = y + v.y;
    double new_z = z + v.z;
    return Vector3 {new_x, new_y, new_z};
}