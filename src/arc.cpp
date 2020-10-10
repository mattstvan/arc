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
  kep.print();
  kep.propagate_to(UTCTime {5566.9}).print();
  Ephemeris ephem;\
  ephem.states.push_back(icrf);
  ephem.print();
  for (std::string line : ephem.format_stk()) {
    std::cout << line << std::endl;
  }
  return 0;
}