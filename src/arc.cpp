#include <cartesian.h>
#include <celestial.h>
#include <ephemeris.h>
#include <keplerian.h>
#include <propagator.h>
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
  UTCTime start = UTCTime {};
  UTCTime stop = UTCTime {86400.0};
  std::vector<ICRF> states = prop.step(start, stop, 300.0);
  Ephemeris eph = Ephemeris {states};
  eph.states[0].print();
  eph.interpolate(UTCTime{150.0}).print();
  eph.states[1].print();
  //eph.write_stk("Test.e");
  return 0;
}