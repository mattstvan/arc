#ifndef EARTH_MODEL_H
#define EARTH_MODEL_H
#include <datetime.h>
#include <vectors.h>

#include <array>

// IAU 1980 value array for nutation model
static const std::array<std::array<double, 9>, 106> IAU_1980_VALUES {
  std::array<double,9> {0, 0, 0, 0, 1, -171996, -174.2, 92025, 8.9},
  std::array<double,9> {0, 0, 2, -2, 2, -13187, -1.6, 5736, -3.1},
  std::array<double,9> {0, 0, 2, 0, 2, -2274, -0.2, 977, -0.5},
  std::array<double,9> {0, 0, 0, 0, 2, 2062, 0.2, -895, 0.5},
  std::array<double,9> {0, 1, 0, 0, 0, 1426, -3.4, 54, -0.1},
  std::array<double,9> {1, 0, 0, 0, 0, 712, 0.1, -7, 0},
  std::array<double,9> {0, 1, 2, -2, 2, -517, 1.2, 224, -0.6},
  std::array<double,9> {0, 0, 2, 0, 1, -386, -0.4, 200, 0},
  std::array<double,9> {1, 0, 2, 0, 2, -301, 0, 129, -0.1},
  std::array<double,9> {0, -1, 2, -2, 2, 217, -0.5, -95, 0.3},
  std::array<double,9> {1, 0, 0, -2, 0, -158, 0, -1, 0},
  std::array<double,9> {0, 0, 2, -2, 1, 129, 0.1, -70, 0},
  std::array<double,9> {-1, 0, 2, 0, 2, 123, 0, -53, 0},
  std::array<double,9> {1, 0, 0, 0, 1, 63, 0.1, -33, 0},
  std::array<double,9> {0, 0, 0, 2, 0, 63, 0, -2, 0},
  std::array<double,9> {-1, 0, 2, 2, 2, -59, 0, 26, 0},
  std::array<double,9> {-1, 0, 0, 0, 1, -58, -0.1, 32, 0},
  std::array<double,9> {1, 0, 2, 0, 1, -51, 0, 27, 0},
  std::array<double,9> {2, 0, 0, -2, 0, 48, 0, 1, 0},
  std::array<double,9> {-2, 0, 2, 0, 1, 46, 0, -24, 0},
  std::array<double,9> {0, 0, 2, 2, 2, -38, 0, 16, 0},
  std::array<double,9> {2, 0, 2, 0, 2, -31, 0, 13, 0},
  std::array<double,9> {2, 0, 0, 0, 0, 29, 0, -1, 0},
  std::array<double,9> {1, 0, 2, -2, 2, 29, 0, -12, 0},
  std::array<double,9> {0, 0, 2, 0, 0, 26, 0, -1, 0},
  std::array<double,9> {0, 0, 2, -2, 0, -22, 0, 0, 0},
  std::array<double,9> {-1, 0, 2, 0, 1, 21, 0, -10, 0},
  std::array<double,9> {0, 2, 0, 0, 0, 17, -0.1, 0, 0},
  std::array<double,9> {0, 2, 2, -2, 2, -16, 0.1, 7, 0},
  std::array<double,9> {-1, 0, 0, 2, 1, 16, 0, -8, 0},
  std::array<double,9> {0, 1, 0, 0, 1, -15, 0, 9, 0},
  std::array<double,9> {1, 0, 0, -2, 1, -13, 0, 7, 0},
  std::array<double,9> {0, -1, 0, 0, 1, -12, 0, 6, 0},
  std::array<double,9> {2, 0, -2, 0, 0, 11, 0, 0, 0},
  std::array<double,9> {-1, 0, 2, 2, 1, -10, 0, 5, 0},
  std::array<double,9> {1, 0, 2, 2, 2, -8, 0, 3, 0},
  std::array<double,9> {0, -1, 2, 0, 2, -7, 0, 3, 0},
  std::array<double,9> {0, 0, 2, 2, 1, -7, 0, 3, 0},
  std::array<double,9> {1, 1, 0, -2, 0, -7, 0, 0, 0},
  std::array<double,9> {0, 1, 2, 0, 2, 7, 0, -3, 0},
  std::array<double,9> {-2, 0, 0, 2, 1, -6, 0, 3, 0},
  std::array<double,9> {0, 0, 0, 2, 1, -6, 0, 3, 0},
  std::array<double,9> {2, 0, 2, -2, 2, 6, 0, -3, 0},
  std::array<double,9> {1, 0, 0, 2, 0, 6, 0, 0, 0},
  std::array<double,9> {1, 0, 2, -2, 1, 6, 0, -3, 0},
  std::array<double,9> {0, 0, 0, -2, 1, -5, 0, 3, 0},
  std::array<double,9> {0, -1, 2, -2, 1, -5, 0, 3, 0},
  std::array<double,9> {2, 0, 2, 0, 1, -5, 0, 3, 0},
  std::array<double,9> {1, -1, 0, 0, 0, 5, 0, 0, 0},
  std::array<double,9> {1, 0, 0, -1, 0, -4, 0, 0, 0},
  std::array<double,9> {0, 0, 0, 1, 0, -4, 0, 0, 0},
  std::array<double,9> {0, 1, 0, -2, 0, -4, 0, 0, 0},
  std::array<double,9> {1, 0, -2, 0, 0, 4, 0, 0, 0},
  std::array<double,9> {2, 0, 0, -2, 1, 4, 0, -2, 0},
  std::array<double,9> {0, 1, 2, -2, 1, 4, 0, -2, 0},
  std::array<double,9> {1, 1, 0, 0, 0, -3, 0, 0, 0},
  std::array<double,9> {1, -1, 0, -1, 0, -3, 0, 0, 0},
  std::array<double,9> {-1, -1, 2, 2, 2, -3, 0, 1, 0},
  std::array<double,9> {0, -1, 2, 2, 2, -3, 0, 1, 0},
  std::array<double,9> {1, -1, 2, 0, 2, -3, 0, 1, 0},
  std::array<double,9> {3, 0, 2, 0, 2, -3, 0, 1, 0},
  std::array<double,9> {-2, 0, 2, 0, 2, -3, 0, 1, 0},
  std::array<double,9> {1, 0, 2, 0, 0, 3, 0, 0, 0},
  std::array<double,9> {-1, 0, 2, 4, 2, -2, 0, 1, 0},
  std::array<double,9> {1, 0, 0, 0, 2, -2, 0, 1, 0},
  std::array<double,9> {-1, 0, 2, -2, 1, -2, 0, 1, 0},
  std::array<double,9> {0, -2, 2, -2, 1, -2, 0, 1, 0},
  std::array<double,9> {-2, 0, 0, 0, 1, -2, 0, 1, 0},
  std::array<double,9> {2, 0, 0, 0, 1, 2, 0, -1, 0},
  std::array<double,9> {3, 0, 0, 0, 0, 2, 0, 0, 0},
  std::array<double,9> {1, 1, 2, 0, 2, 2, 0, -1, 0},
  std::array<double,9> {0, 0, 2, 1, 2, 2, 0, -1, 0},
  std::array<double,9> {1, 0, 0, 2, 1, -1, 0, 0, 0},
  std::array<double,9> {1, 0, 2, 2, 1, -1, 0, 1, 0},
  std::array<double,9> {1, 1, 0, -2, 1, -1, 0, 0, 0},
  std::array<double,9> {0, 1, 0, 2, 0, -1, 0, 0, 0},
  std::array<double,9> {0, 1, 2, -2, 0, -1, 0, 0, 0},
  std::array<double,9> {0, 1, -2, 2, 0, -1, 0, 0, 0},
  std::array<double,9> {1, 0, -2, 2, 0, -1, 0, 0, 0},
  std::array<double,9> {1, 0, -2, -2, 0, -1, 0, 0, 0},
  std::array<double,9> {1, 0, 2, -2, 0, -1, 0, 0, 0},
  std::array<double,9> {1, 0, 0, -4, 0, -1, 0, 0, 0},
  std::array<double,9> {2, 0, 0, -4, 0, -1, 0, 0, 0},
  std::array<double,9> {0, 0, 2, 4, 2, -1, 0, 0, 0},
  std::array<double,9> {0, 0, 2, -1, 2, -1, 0, 0, 0},
  std::array<double,9> {-2, 0, 2, 4, 2, -1, 0, 1, 0},
  std::array<double,9> {2, 0, 2, 2, 2, -1, 0, 0, 0},
  std::array<double,9> {0, -1, 2, 0, 1, -1, 0, 0, 0},
  std::array<double,9> {0, 0, -2, 0, 1, -1, 0, 0, 0},
  std::array<double,9> {0, 0, 4, -2, 2, 1, 0, 0, 0},
  std::array<double,9> {0, 1, 0, 0, 2, 1, 0, 0, 0},
  std::array<double,9> {1, 1, 2, -2, 2, 1, 0, -1, 0},
  std::array<double,9> {3, 0, 2, -2, 2, 1, 0, 0, 0},
  std::array<double,9> {-2, 0, 2, 2, 2, 1, 0, -1, 0},
  std::array<double,9> {-1, 0, 0, 0, 2, 1, 0, -1, 0},
  std::array<double,9> {0, 0, -2, 2, 1, 1, 0, 0, 0},
  std::array<double,9> {0, 1, 2, 0, 1, 1, 0, 0, 0},
  std::array<double,9> {-1, 0, 4, 0, 2, 1, 0, 0, 0},
  std::array<double,9> {2, 1, 0, -2, 0, 1, 0, 0, 0},
  std::array<double,9> {2, 0, 0, 2, 0, 1, 0, 0, 0},
  std::array<double,9> {2, 0, 2, -2, 1, 1, 0, -1, 0},
  std::array<double,9> {2, 0, -2, 0, 1, 1, 0, 0, 0},
  std::array<double,9> {1, -1, 0, -2, 0, 1, 0, 0, 0},
  std::array<double,9> {-1, 0, 0, 1, 1, 1, 0, 0, 0},
  std::array<double,9> {-1, -1, 0, 2, 1, 1, 0, 0, 0},
  std::array<double,9> {0, 1, 0, 1, 0, 1, 0, 0, 0}
};

// Return Earth's rotation vector, in radians per second
// TODO: Implement LOD variations from IERS finals.all
Vector3 earth_rotation(DateTime &epoch);

/*
Calculate the [zeta, theta, zed] angles of precession in radians

Currently uses IAU 1980 precession
*/
std::array<double, 3> earth_precession(DateTime &epoch);

/* 
Calculate the delta psi, delta epsilon, and mean epsilon angles of nutation in radians

Currently uses IAU 1980 nutation
*/
std::array<double, 3> earth_nutation(DateTime &epoch, int n = 106);

#endif