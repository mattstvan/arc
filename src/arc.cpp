#include <icrf.h>
#include <itrf.h>
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
  DateTime start { "2020-10-18T15:00:00" };
  DateTime stop { "2020-10-19T15:00:00" };
  Vector3 pos {-698891.686, 6023436.003, 3041793.014};
  Vector3 vel {-4987.520, -3082.634, 4941.720};
  ICRF test {EARTH, start, pos, vel};
  ITRF test2 {test};
  test2.print();
  return 0;
}