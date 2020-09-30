#ifndef VECTORS_H
#define VECTORS_H

// Three-element vector class
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

    // Calculate the magnitude
    double mag();

    // Print to std::cout
    void print();
};

#endif