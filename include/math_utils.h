#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

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
  } else {
    return a2;
  }
}

#endif