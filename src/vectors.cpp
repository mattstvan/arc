#include <iostream>
#include <cmath>
#include <vectors.h>

// Default constructor
Vector3::Vector3() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
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
}

// Calculate the magnitude
double Vector3::mag() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}