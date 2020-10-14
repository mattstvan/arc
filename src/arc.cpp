#include <cartesian.h>
#include <celestial.h>
#include <ephemeris.h>
#include <keplerian.h>
#include <propagator.h>
#include <interpolator.h>
#include <utctime.h>
#include <vectors.h>

#include <ctime>
#include <iostream>

int main() {
  ICRF icrf =
      ICRF{EARTH, UTCTime{}, Vector3{-698891.686, 6023436.003, 3041793.014},
           Vector3{-4987.520, -3082.634, 4941.720}};
  KeplerianElements kep = KeplerianElements{icrf};
  KeplerianPropagator prop = KeplerianPropagator{kep};
  UTCTime start = UTCTime {0};
  UTCTime stop = UTCTime {86400.0};
  // Ephemeris eph = prop.step(start, stop, 300.0);
  // Ephemeris eph2 = InterpolatorPropagator{eph}.step(start, stop, 60);
  ICRF test = EARTH.propagate(start);
  test.print();
  //test.print();
  // eph2.write_stk("Test2.e");
  return 0;
}