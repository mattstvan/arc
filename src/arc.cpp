#include <iostream>
#include <vectors.h>
#include <utctime.h>
#include <cartesian.h>
#include <celestial.h>
#include <ctime>

using namespace std;

int main() {
    ICRF icrf;
    icrf.print();
    UTCTime epoch = UTCTime {50000.0};
    ICRF icrf2 = ICRF {};
    icrf2.print();
    return 0;
}