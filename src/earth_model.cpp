#include <earth_model.h>
#include <celestial.h>
#include <data_files.h>
#include <math_utils.h>

// Return Earth's rotation vector, in radians per second
// TODO: Implement LOD variations from IERS finals.all
Vector3 earth_rotation(DateTime &epoch) {
  // Earth rotation vector
  return Vector3{0.0, 0.0, 7.2921158553e-5};
  // return EARTH.rotation.scale(1.0 - finals.lod / 86400.0);
};

/*
Calculate the [zeta, theta, zed] angles of precession in radians

Currently uses IAU 1980 precession
*/
std::array<double, 3> earth_precession(DateTime &epoch) {
  // Algorithim requires epoch in TDB scale, expressed in Julian Centuries
  double t = epoch.tdb().julian_centuries();
  // Evaluate precession polynomials using Julian centuries value
  double zeta = eval_poly(t, std::vector<double> {0.0, 0.6406161, 0.0000839, 5.0e-6});
  double theta = eval_poly(t, std::vector<double> {0.0, 0.556753, -0.0001185, -1.16e-5});
  double zed = eval_poly(t, std::vector<double> {0.0, 0.6406161, 0.0003041, 5.1e-6});
  // Convert polynomial outputs (degrees) to radians and return
  return std::array<double, 3> {radians(zeta), radians(theta), radians(zed)};
}

/* 
Calculate the delta psi, delta epsilon, and mean epsilon angles of nutation in radians

Currently uses IAU 1980 nutation
*/
std::array<double, 3> earth_nutation(DateTime &epoch, int n) {
    double r = 360.0;
    // Algorithim requires epoch in TDB scale, expressed in Julian Centuries
    double t = epoch.tdb().julian_centuries();
    // Compute value of Mean Epsilon
    double mean_eps = eval_poly(t, std::vector<double> {
        23.439291,
        -0.013004,
        -1.64e-7,
        5.04e-7
    });
    mean_eps = radians(mean_eps);
    // Moon Anomaly
    double moon_anom = eval_poly(t, std::vector<double> {
        134.96340251,
        1325.0 * r + 198.8675605,
        0.0088553,
        1.4343e-5
    });
    // Moon Latitude
    double moon_lat = eval_poly(t, std::vector<double> {
        93.27209062,
        1342.0 * r + 82.0174577,
        -0.003542,
        -2.88e-7
    });
    // Moon RAAN
    double moon_raan = eval_poly(t, std::vector<double> {
        125.04455501,
        -(5.0 * r + 134.1361851),
        0.0020756,
        2.139e-6
    });
    // Sun anomaly
    double sun_anom = eval_poly(t, std::vector<double> {
        357.52910918,
        99.0 * r + 359.0502911,
        -0.0001537,
        3.8e-8
    });
    // Sun Longitude
    double sun_e_long = eval_poly(t, std::vector<double> {
        297.85019547,
        1236.0 * r + 307.1114469,
        -0.0017696,
        1.831e-6
    });
    // Compute values of Delta-Psi and Delta-Epsilon
    double delta_psi = 0.0;
    double delta_eps = 0.0;
    // Iterate through the IAU 1980 nutation values
    for (int i = 0; i < n; i++) {
        std::array<double, 9> ln = IAU_1980_VALUES[i];
        double a1 = ln[0];
        double a2 = ln[1];
        double a3 = ln[2];
        double a4 = ln[3];
        double a5 = ln[4];
        double Ai = ln[5];
        double Bi = ln[6];
        double Ci = ln[7];
        double Di = ln[8];
        // Build the nutation argument
        double arg = radians(
            a1 * moon_anom +
            a2 * sun_anom +
            a3 * moon_lat + 
            a4 * sun_e_long +
            a5 * moon_raan
        );
        // Coefficients
        double sin_c = Ai + Bi * t;
        double cos_c = Ci + Di * t;
        // Compute delta psi
        delta_psi += sin_c * sin(arg);
        delta_eps += cos_c * cos(arg);
    }
    // Convert results from 0.0001 arcseconds to radians
    delta_psi = marcsec_to_radians(delta_psi);
    delta_eps = marcsec_to_radians(delta_eps);
    // Return complete nutation array
    return std::array<double, 3> {delta_psi, delta_eps, mean_eps};
}