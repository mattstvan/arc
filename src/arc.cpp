#include <cartesian.h>
#include <celestial.h>
#include <keplerian.h>
#include <utctime.h>
#include <vectors.h>
#include <ephemeris.h>
#include <ctime>
#include <iostream>

int main() {
  ICRF icrf{EARTH, UTCTime{}, Vector3{-698891.686, 6023436.003, 3041793.014},
            Vector3{-4987.520, -3082.634, 4941.720}};
  KeplerianElements kep{icrf};
  ICRF icrf2 {kep};
  icrf.print();
  icrf2.print();
  std::cout << icrf.position.distance(icrf2.position) << std::endl;
  std::cout << icrf.velocity.distance(icrf2.velocity) << std::endl;
  return 0;
}