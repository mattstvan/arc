#ifndef VECTORS_H
#define VECTORS_H

// Three-element vector
class Vector3 {
    public:
        // "X" or "I" component
        double x;
        // "Y" or "J" component
        double y;
        // "Z" or "K" component
        double z;

    // Default constructor
    Vector3();

    // Constructor using doubles
    Vector3(double x, double y, double z);

    // Print to std::cout
    void print();

    // Calculate the magnitude
    double mag();

    // Scale by a scalar value using element-wise multiplication
    Vector3 scale(double scalar);

    // Calculate the unit vector
    Vector3 unit();

    // Add another Vector3 using element-wise addition
    Vector3 add(Vector3 v);
};

#endif