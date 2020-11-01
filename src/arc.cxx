#include <icrf.h>
#include <itrf.h>
#include <celestial.h>
#include <datetime.h>
#include <vectors.h>
#include <force_model.h>
#include <gravity.h>
#include <rungekutta4.h>
#include <body_propagation.h>
#include <ephemeris.h>
#include <interpolator.h>
#include <data_files.h>
#include <earth_model.h>
#include <exceptions.h>
#include <iostream>
#include <iomanip>

int main() {
  try {
    DateTime start { "2020-10-18T15:00:00" };
    DateTime stop { "2020-10-19T15:00:00" };
    Vector3 pos {-698891.686, 6023436.003, 3041793.014};
    Vector3 vel {-4987.520, -3082.634, 4941.720};
    ICRF ic {EARTH, start, pos, vel};
  } catch (ArcException err) {
    std::cout << err.what() << std::endl;
    return 1;
  }
  return 0;
}