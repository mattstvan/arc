#ifndef VECTORS_H
#define VECTORS_H
#include <array>
#include <cmath>
#include <iostream>

/*
Three-element vector

Vector with X,Y,Z or I,J,K components. Typically represents a single construct in 3D space.
*/
class Vector3 {
public:
  // "X" or "I" component
  double x;
  // "Y" or "J" component
  double y;
  // "Z" or "K" component
  double z;

  /*
  Default constructor

  Sets all elements to zero
  */
  Vector3();

  /*
  Constructor using doubles

  @param x "X" or "I" value
  @param y "Y" or "J" value
  @param z "Z" or "K" value
  */
  Vector3(double x, double y, double z);

  /*
  Calculate the magnitude

  @returns Magnitude of this vector
  */
  double mag();

  /*
  Scale by a scalar value using element-wise multiplication

  @param scalar Number by which to multiply each element
  @returns (vectors::Vector3) scaled vector
  */
  Vector3 scale(double scalar);

  /*
  Calculate the unit vector

  @returns (vectors::Vector3) unit vector
  */
  Vector3 unit();

  /*
  Add another Vector3 using element-wise addition

  @param v Vector to add element-wise
  @returns (vectors::Vector3) Vector representing the element-wise sum
  */
  Vector3 add(Vector3& v);

  /*
  Calculate a new Vector3 representing the inverse (negated elements)

  @returns (vectors::Vector3) The same vector, scaled by -1
  */
  Vector3 inverse();

  /*
  Distance to another Vector3, assuming that
  both coordinate systems/origins are the same

  @param v The vector from which to calculate distance
  @returns (double) distance between this and the vector v
  */
  double distance(Vector3& v);

  /*
  Dot product with another Vector3

  @param v The vector to use for dot product calculation
  @returns (double) Dot product of this and the vector v
  */
  double dot(Vector3& v);

  /*
  Cross product with another Vector3

  @param v The vector to use for cross product calculation
  @returns (vector::Vector3) Cross product of this and the vector v
  */
  Vector3 cross(Vector3& v);

  /*
  Rotate along the x-axis

  @param theta The angle of rotation
  @returns (vector::Vector3) the rotated vector
  */
  Vector3 rot_x(double theta);

  /*
  Rotate along the y-axis

  @param theta The angle of rotation
  @returns (vector::Vector3) the rotated vector
  */
  Vector3 rot_y(double theta);

  /*
  Rotate along the z-axis

  @param theta The angle of rotation
  @returns (vector::Vector3) the rotated vector
  */
  Vector3 rot_z(double theta);

  /*
  Calculate angle to another Vector3

  @param v The vector to which to calculate the angle
  @returns (double) The angle between this and the vector v
  */
  double angle(Vector3& v);

  /*
  Change coordinates to relative position from a 
  new origin, assuming both vectors have the same starting origin

  @param origin Vector to use as the new origin
  @returns (vectors::Vector3) This vector centered around the new origin vector
  */
  Vector3 change_origin(Vector3& origin);
};

/*
Vector3 operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream &out, Vector3& v);

// Element-wise addition
Vector3 operator + (Vector3& v_1, Vector3& v_2);

// Element-wise subtraction
Vector3 operator - (Vector3& v_1, Vector3& v_2);

// Element-wise multiplication by scalar
Vector3 operator * (Vector3& v_1, double scalar);

// Element-wise division by scalar
Vector3 operator / (Vector3& v_1, double scalar);

// Dot product with another Vector3
double operator * (Vector3& v_1, Vector3& v_2);

// Cross product with another Vector3
Vector3 operator % (Vector3& v_1, Vector3& v_2);


/*
Six-element vector

Typically represents the combination of two constructs in 3D space.
*/
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

  /*
  Default constructor

  Sets all elements to zero
  */
  Vector6();

  /*
  Constructor using doubles

  @param a "A" or "X1" value
  @param b "B" or "Y1" value
  @param c "C" or "Z1" value
  @param x "X" or "X2" value
  @param y "Y" or "Y2" value
  @param z "Z" or "Z2" value
  */
  Vector6(double a, double b, double c, double x, double y, double z);

  /*
  Constructor using two Vector3 instances as {a.x, a.y, a.z, b.x, b.y, b.z}

  @param a First vector
  @param b Second vector
  @returns (vectors::Vector6) combined a/b vector
  */
  Vector6(Vector3& a, Vector3& b);

  /*
  Add another Vector6 using element-wise addition

  @param v Vector to add element-wise
  @returns (vectors::Vector6) Vector representing the element-wise sum
  */
  Vector6 add(Vector6& v);

  /*
  Scale by a scalar value using element-wise multiplication

  @param scalar Number by which to multiply each element
  @returns (vectors::Vector6) scaled vector
  */
  Vector6 scale(double scalar);

  /*
  Split the elements into two Vector3 instances

  @returns (std::array<Vector3, 2>) Array of this vector split by first/last 3 elements
  */
  std::array<Vector3, 2> split();
};

/*
Vector6 operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream &out, Vector6& v);

// Element-wise addition
Vector6 operator + (Vector6& v_1, Vector6& v_2);

// Element-wise subtraction
Vector6 operator - (Vector6& v_1, Vector6& v_2);

// Element-wise multiplication by scalar
Vector6 operator * (Vector6& v_1, double scalar);

// Element-wise division by scalar
Vector6 operator / (Vector6& v_1, double scalar);

#endif