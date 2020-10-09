#include <vectors.h>
#include <utctime.h>
#include <cartesian.h>
#include <celestial.h>
#include <keplerian.h>
#include <ctime>
#include <iostream>

int main() {
    ICRF icrf {EARTH, UTCTime{}, Vector3 {-698891.686, 6023436.003, 3041793.014}, Vector3 {-4987.520, -3082.634, 4941.720}};
    KeplerianElements kep {icrf};
    icrf.print();
    kep.print();
    return 0;
}