#include <vectors.h>
#include <utctime.h>
#include <cartesian.h>
#include <celestial.h>
#include <keplerian.h>
#include <ctime>
#include <iostream>

int main() {
    ICRF icrf;
    icrf.position = Vector3 {-698891.686, 6023436.003, 3041793.014};
    icrf.velocity = Vector3 {-4987.520, -3082.634, 4941.720};
    KeplerianElements kep = KeplerianElements {icrf};
    kep.print();
    return 0;
}