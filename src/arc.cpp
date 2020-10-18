#include <cartesian.h>
#include <celestial.h>
#include <utctime.h>
#include <vectors.h>
#include <rungekutta4.h>
#include <ephemeris.h>

#include <iostream>

int main() {
  ICRF icrf{
    EARTH,
    UTCTime{"2020-10-18T15:00:00"},
    Vector3{-698891.686, 6023436.003, 3041793.014},
    Vector3{-4987.520, -3082.634, 4941.720}
  };
  UTCTime start { "2020-10-18T15:00:00" };
  UTCTime stop { "2020-10-19T15:00:00" };
  RungeKutta4 prop = RungeKutta4 {icrf};
  prop.step_size = 1.0;
  Ephemeris ephem = prop.step(start, stop, 60.0);
  ephem.write_stk("test_ephem.e");
  return 0;
}