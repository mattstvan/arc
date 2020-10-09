#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <vector>
#include <math.h>

// Evaluate a polynomial given a variable (x) and its coefficients
// Exponents start at zero and increase to the order given by the length of 'coeffs'
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

#endif