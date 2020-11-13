#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <vector>

// Convert an angle in degrees to radians
double radians(double deg);

// Convert an angle in radians to degrees
double degrees(double rad);

// Convert an angle in arcseconds to radians
double arcsec_to_radians(double arcsec);

// Convert an angle in milliarcseconds to radians
double marcsec_to_radians(double marcsec);

// Evaluate a polynomial given a variable (x) and its coefficients
// Exponents start at zero and increase to the order given by the length of
// 'coeffs'
double eval_poly(double x, std::vector<double> coeffs);

// Return the angle (original or inverse) that exists in the half plane of the
// match argument (m)
double match_half_plane(double angle, double m);

#endif