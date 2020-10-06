#ifndef VECTORS_H
#define VECTORS_H
#include <array>

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
    Vector3 add(Vector3& v);

    // Calculate a new Vector3 representing the inverse (negated elements)
    Vector3 inverse();

    // Distance to another Vector3
    double distance(Vector3& v);

    // Dot product with another Vector3
    double dot(Vector3& v);

    // Cross product with another Vector3
    Vector3 cross(Vector3& v);

    // Rotate along the x-axis
    Vector3 rot_x(double theta);

    // Rotate along the y-axis
    Vector3 rot_y(double theta);

    // Rotate along the z-axis
    Vector3 rot_z(double theta);

    // Calculate angle to another Vector3
    double angle(Vector3& v);

    // Change coordinates to relative position from a new origin
    Vector3 change_origin(Vector3& origin);
};

// Six-element vector
class Vector6 {
    public:
        // "A" or "I_1" component
        double a;
        // "B" or "J_1" component
        double b;
        // "C" or "K_1" component
        double c;
        // "X" or "I_2" component
        double x;
        // "Y" or "J_2" component
        double y;
        // "Z" or "K_2" component
        double z;

    // Default constructor
    Vector6();

    // Constructor using doubles
    Vector6(double a, double b, double c, double x, double y, double z);

    // Constructor using two Vector3 instances
    Vector6(Vector3& a, Vector3& b);

    // Print to std::cout
    void print();
    
    // Add another Vector6 using element-wise addition
    Vector6 add(Vector6& v);

    // Scale by a scalar value using element-wise multiplication
    Vector6 scale(double scalar);

    // Split the elements into two Vector3 instances
    std::array<Vector3, 2> split();
};

#endif