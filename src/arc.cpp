#include <cartesian.h>
#include <celestial.h>
#include <keplerian.h>
#include <utctime.h>
#include <vectors.h>

#include <ctime>
#include <iostream>

int main() {
  ICRF icrf{EARTH, UTCTime{}, Vector3{-698891.686, 6023436.003, 3041793.014},
            Vector3{-4987.520, -3082.634, 4941.720}};
  KeplerianElements kep{icrf};
  kep.print();
  kep.propagate_to(UTCTime {5566.9}).print();
  return 0;
}