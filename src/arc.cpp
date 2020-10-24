#include <cartesian.h>
#include <celestial.h>
#include <datetime.h>
#include <vectors.h>
#include <force_model.h>
#include <gravity.h>
#include <rungekutta4.h>
#include <ephemeris.h>
#include <data_files.h>
#include <earth_model.h>
#include <iostream>
#include <iomanip>

int main() {
  DateTime test = {"2020-10-24T00:00:00"};
  std::array<double, 3> p_test_p = earth_precession(test);
  std::array<double, 3> p_test_n = earth_nutation(test);
  std::cout << std::scientific << std::setprecision(14) << p_test_p[0] << " " << p_test_p[1] << " " << p_test_p[2] << std::endl;
  std::cout << std::scientific << std::setprecision(14) << p_test_n[0] << " " << p_test_n[1] << " " << p_test_n[2] << std::endl;
  return 0;
}