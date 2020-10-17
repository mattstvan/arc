#include <cartesian.h>
#include <celestial.h>
#include <utctime.h>
#include <vectors.h>
#include <propagator.h>
#include <ephemeris.h>

#include <iostream>

int main() {
  ICRF icrf{
    EARTH,
    UTCTime{},
    Vector3{-698891.686, 6023436.003, 3041793.014},
    Vector3{-4987.520, -3082.634, 4941.720}
  };
  UTCTime start { 0 };
  UTCTime stop { 86400.0 };
  NumericalPropagator prop = NumericalPropagator {icrf};
  prop.step_size = 1.0;
  Ephemeris ephem = prop.step(start, stop, 60.0);
  ephem.write_stk("test_ephem.e");
  return 0;
}