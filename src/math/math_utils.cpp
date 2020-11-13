#include <math_utils.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

// Convert an angle in degrees to radians
double radians(double deg) {
  return deg * M_PI / 180.0; 
}

// Convert an angle in radians to degrees
double degrees(double rad) {
  return rad * 180.0 / M_PI;
}

// Convert an angle in arcseconds to radians
double arcsec_to_radians(double arcsec) {
    return arcsec * (1.0 / 60.0 / 60.0) * M_PI / 180;
}

// Convert an angle in milliarcseconds to radians
double marcsec_to_radians(double marcsec) {
    return marcsec * (1.0 / 60.0 / 60.0 / 10000.0) * M_PI / 180;
}

// Evaluate a polynomial given a variable (x) and its coefficients
// Exponents start at zero and increase to the order given by the length of
// 'coeffs'
double eval_poly(double x, std::vector<double> coeffs) {
  // Total value of the expression
  double output = 0.0;
  // Add the value of ax^i to the output variable,
  // where a is the value stored in coeffs[i]
  for (int n = 0; n < coeffs.size(); n++) {
    output += coeffs[n] * pow(x, n);
  }
  return output;
}

// Return the angle (original or inverse) that exists in the half plane of the
// match argument (m)
double match_half_plane(double angle, double m) {
  double a1 = angle;
  double a2 = (2.0 * M_PI) - angle;
  double d1 = atan2(sin(a1 - m), cos(a1 - m));
  double d2 = atan2(sin(a2 - m), cos(a2 - m));
  if (fabs(d1) < fabs(d2)) {
    return a1;
  }
  else {
    return a2;
  }
}