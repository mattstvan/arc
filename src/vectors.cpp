#include <vectors.h>

/*
Three-element vector methods
*/

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
}

// Calculate the magnitude
double Vector3::mag() { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

// Scale by a scalar value using element-wise multiplication
Vector3 Vector3::scale(double scalar) {
  double new_x = x * scalar;
  double new_y = y * scalar;
  double new_z = z * scalar;
  return Vector3{ new_x, new_y, new_z };
}

// Calculate the unit vector
Vector3 Vector3::unit() { return scale(1.0 / mag()); }

// Add another Vector3 using element-wise addition
Vector3 Vector3::add(Vector3& v) {
  double new_x = x + v.x;
  double new_y = y + v.y;
  double new_z = z + v.z;
  return Vector3{ new_x, new_y, new_z };
}

// Calculate a new Vector3 representing the inverse (negated elements)
Vector3 Vector3::inverse() { return scale(-1.0); }

// Distance to another Vector3, assuming that both coordinate systems/origins are the same
double Vector3::distance(Vector3& v) {
  double dx = x - v.x;
  double dy = y - v.y;
  double dz = z - v.z;
  return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}

// Dot product with another Vector3
double Vector3::dot(Vector3& v) {
  double mx = x * v.x;
  double my = y * v.y;
  double mz = z * v.z;
  return mx + my + mz;
}

// Cross product with another Vector3
Vector3 Vector3::cross(Vector3& v) {
  double new_x = y * v.z - z * v.y;
  double new_y = z * v.x - x * v.z;
  double new_z = x * v.y - y * v.x;
  return Vector3{ new_x, new_y, new_z };
}

// Rotate along the x-axis
Vector3 Vector3::rot_x(double theta) {
  double cos_t = cos(theta);
  double sin_t = sin(theta);
  double new_x = 1.0 * x + 0.0 * y + 0.0 * z;
  double new_y = 0.0 * x + cos_t * y + sin_t * z;
  double new_z = 0.0 * x + -sin_t * y + cos_t * z;
  return Vector3{ new_x, new_y, new_z };
}

// Rotate along the y-axis
Vector3 Vector3::rot_y(double theta) {
  double cos_t = cos(theta);
  double sin_t = sin(theta);
  double new_x = cos_t * x + 0.0 * y + -sin_t * z;
  double new_y = 0.0 * x + 1.0 * y + 0.0 * z;
  double new_z = sin_t * x + 0.0 * y + cos_t * z;
  return Vector3{ new_x, new_y, new_z };
}

// Rotate along the z-axis
Vector3 Vector3::rot_z(double theta) {
  double cos_t = cos(theta);
  double sin_t = sin(theta);
  double new_x = cos_t * x + sin_t * y + 0.0 * z;
  double new_y = -sin_t * x + cos_t * y + 0.0 * z;
  double new_z = 0.0 * x + 0.0 * y + 1.0 * z;
  return Vector3{ new_x, new_y, new_z };
}

// Calculate angle to another Vector3
double Vector3::angle(Vector3& v) { return acos(dot(v) / (mag() * v.mag())); }


// Change coordinates to relative position from a new origin, assuming both vectors have the same starting origin
Vector3 Vector3::change_origin(Vector3& origin) {
  Vector3 delta = origin.inverse();
  return add(delta);
}

/*
Vector3 operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream& out, Vector3& v) {
  out << "[Vector3] { X: " << v.x << ", Y: " << v.y << ", Z: " << v.z << " }";
  return out;
}

// Element-wise addition
Vector3 operator + (Vector3& v_1, Vector3& v_2) {
  return v_1.add(v_2);
}

// Element-wise subtraction
Vector3 operator - (Vector3& v_1, Vector3& v_2) {
  Vector3 inv = v_2.inverse();
  return v_1.add(inv);
}

// Element-wise multiplication by scalar
Vector3 operator * (Vector3& v_1, double scalar) {
  return v_1.scale(scalar);
}

// Element-wise division by scalar
Vector3 operator / (Vector3& v_1, double scalar) {
  return v_1.scale(1.0 / scalar);
}

// Dot product with another Vector3
double operator * (Vector3& v_1, Vector3& v_2) {
  return v_1.dot(v_2);
}

// Cross product with another Vector3
Vector3 operator % (Vector3& v_1, Vector3& v_2) {
  return v_1.cross(v_2);
}

/*
Six-element vector methods
*/

Vector6::Vector6() {
  this->a = 0.0;
  this->b = 0.0;
  this->c = 0.0;
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}

Vector6::Vector6(double a, double b, double c, double x, double y, double z) {
  this->a = a;
  this->b = b;
  this->c = c;
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector6::Vector6(Vector3& a, Vector3& b) {
  this->a = a.x;
  this->b = a.y;
  this->c = a.z;
  this->x = b.x;
  this->y = b.y;
  this->z = b.z;
}

Vector6 Vector6::add(Vector6& v) {
  double da = a + v.a;
  double db = b + v.b;
  double dc = c + v.c;
  double dx = x + v.x;
  double dy = y + v.y;
  double dz = z + v.z;
  return Vector6{ da, db, dc, dx, dy, dz };
}

Vector6 Vector6::scale(double scalar) {
  double new_a = a * scalar;
  double new_b = b * scalar;
  double new_c = c * scalar;
  double new_x = x * scalar;
  double new_y = y * scalar;
  double new_z = z * scalar;
  return Vector6{ new_a, new_b, new_c, new_x, new_y, new_z };
}

std::array<Vector3, 2> Vector6::split() {
  return { Vector3{a, b, c}, Vector3{x, y, z} };
}

/*
Vector6 operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream& out, Vector6& v) {
  out << "[Vector6] { A: " << v.a << ", B: " << v.b << ", C: " << v.c
    << ", X: " << v.x << ", Y: " << v.y << ", Z: " << v.z << " }";
  return out;
}

// Element-wise addition
Vector6 operator + (Vector6& v_1, Vector6& v_2) {
  return v_1.add(v_2);
}

// Element-wise subtraction
Vector6 operator - (Vector6& v_1, Vector6& v_2) {
  Vector6 inv = v_2.scale(-1);
  return v_1.add(inv);
}

// Element-wise multiplication by scalar
Vector6 operator * (Vector6& v_1, double scalar) {
  return v_1.scale(scalar);
}

// Element-wise division by scalar
Vector6 operator / (Vector6& v_1, double scalar) {
  return v_1.scale(1.0 / scalar);
}