#include <cartesian.h>
#include <celestial.h>
#include <utctime.h>
#include <vectors.h>
#include <force_model.h>
#include <gravity.h>
#include <rungekutta4.h>
#include <ephemeris.h>

#include <iostream>

int main() {
  UTCTime start { "2020-10-18T15:00:00" };
  UTCTime stop { "2020-10-19T15:00:00" };
  Vector3 pos {-698891.686, 6023436.003, 3041793.014};
  Vector3 vel {-4987.520, -3082.634, 4941.720};
  ICRF icrf {EARTH, start, pos, vel};
  GravityModel gm1 {EARTH, false, 0, 0};
  GravityModel gm2 {SUN, false, 0, 0};
  GravityModel gm3 {LUNA, false, 0, 0};
  ForceModel fm {std::vector<GravityModel> {gm1, gm2, gm3}};
  RungeKutta4 prop = RungeKutta4 {icrf, 60.0, fm};
  Ephemeris ephem = prop.step(start, stop, 60.0);
  ephem.write_stk("test_ephem.e");
  return 0;
}