#include <cartesian.h>
#include <keplerian.h>
#include <math_utils.h>

/*
Keplerian elements methods
*/

// Default constructor
KeplerianElements::KeplerianElements() {
  this->central_body = SUN;
  this->epoch = UTCTime{};
  this->a = 0.0;
  this->e = 0.0;
  this->i = 0.0;
  this->o = 0.0;
  this->w = 0.0;
  this->v = 0.0;
}

// Direct constructor
KeplerianElements::KeplerianElements(CelestialBody body, UTCTime epoch,
  double a, double e, double i, double o,
  double w, double v) {
  this->central_body = body;
  this->epoch = epoch;
  this->a = a;
  this->e = e;
  this->i = i;
  this->o = o;
  this->w = w;
  this->v = v;
}

// Constructor using Cartesian instance
KeplerianElements::KeplerianElements(Cartesian vector) {
  // Create some constants to avoid repeat calls
  const double r_mag = vector.position.mag();
  const double v_mag = vector.velocity.mag();
  // Copy the central body and epoch
  this->central_body = vector.central_body;
  this->epoch = vector.epoch;
  // Calculate Semi-major axis
  double mu = vector.central_body.mu;
  double energy = pow(v_mag, 2.0) / 2.0 - mu / r_mag;
  double a = -(mu / (2.0 * energy));
  this->a = a;
  // Calculate eccentricity vector and its magnitude (e)
  Vector3 e_vec_a = vector.position.scale(pow(v_mag, 2.0) - mu / r_mag);
  Vector3 e_vec_b = vector.velocity.scale(vector.position.dot(vector.velocity));
  Vector3 e_vec = e_vec_a.add(e_vec_b.inverse()).scale(1.0 / mu);
  double e = e_vec.mag();
  this->e = e;
  Vector3 h = vector.position.cross(vector.velocity);
  // Inclination
  double i = acos(h.z / h.mag());
  this->i = i;
  Vector3 n = (Vector3{ 0.0, 0.0, 1.0 }).cross(h);
  // RAAN
  double o = acos(n.x / n.mag());
  // Argument of periapsis
  double w = acos(n.dot(e_vec) / (n.mag() * e));
  // True anomaly
  double v = acos(e_vec.dot(vector.position) / (e * r_mag));
  // Sanity check RAAN
  if (n.y < 0.0) {
    o = 2.0 * M_PI - o;
  };
  if (isnan(o)) {
    o = 0.0;
  };
  // Sanity check argument of periapsis
  if (e_vec.z < 0.0) {
    w = 2.0 * M_PI - w;
  };
  if (isnan(w)) {
    w = 0.0;
  };
  // Sanity check true anomaly
  if (vector.position.dot(vector.velocity) < 0.0) {
    v = 2.0 * M_PI - v;
  };
  if (isnan(v)) {
    v = 0.0;
  };
  // Set final variables
  this->o = o;
  this->w = w;
  this->v = v;
}

// Print to std::cout
void KeplerianElements::print() {
  std::cout << "[KeplerianElements]" << std::endl;
  std::cout << " Central Body: ";
  central_body.print();
  std::cout << " Epoch: ";
  epoch.print();
  std::cout << " A: " << a << std::endl;
  std::cout << " E: " << e << std::endl;
  std::cout << " I: " << i * (180.0 / M_PI) << std::endl;
  std::cout << " O: " << o * (180.0 / M_PI) << std::endl;
  std::cout << " W: " << w * (180.0 / M_PI) << std::endl;
  std::cout << " V: " << v * (180.0 / M_PI) << std::endl;
}

// Compute mean motion
double KeplerianElements::mean_motion() {
  return sqrt(central_body.mu / pow(a, 3.0));
}


// Propagate the True Anomaly of the elements to a specified epoch
// Ref: Montenbruck, O., & Gill, E. (2012). Prediction of Unperturbed Satellite Orbits.
// In Satellite orbits: Models, methods, and applications (pp. 22-32). Berlin: Springer-Verlag.
KeplerianElements KeplerianElements::propagate_to(UTCTime t) {
  // Get delta between the requested time and the initial state epoch
  double delta = t.difference(epoch);
  // Calculate mean motion
  double n = mean_motion();
  // Make an initial estimate of the Eccentric Anomaly and improve it using True
  // Anomaly
  double ecc_anom = acos((e + cos(v)) / (1.0 + e * cos(v)));
  ecc_anom = match_half_plane(ecc_anom, v);
  // Make an initial estimate of the Mean Anomaly and improve it using Eccentric
  // Anomaly
  double mean_anom = ecc_anom - e * sin(ecc_anom);
  mean_anom = match_half_plane(mean_anom, ecc_anom);
  mean_anom = fmod(mean_anom + n * delta, 2.0 * M_PI);
  ecc_anom = mean_anom;
  // Set up iteration variables
  int iter = 0;
  double ea_temp;
  // Iterate on the Eccentric Anomaly to improve the estimate
  while (iter < 32) {
    ea_temp = mean_anom + e * sin(ecc_anom);
    if (fabs(ea_temp - ecc_anom) < 1e-12) {
      break;
    }
    iter += 1;
    ecc_anom = ea_temp;
  }
  // Make an inital estimate of final True Anomaly and improve it using the
  // final Eccentric anomaly
  double v_final = acos((cos(ecc_anom) - e) / (1.0 - e * cos(ecc_anom)));
  v_final = match_half_plane(v_final, ecc_anom);
  // Create new Keplerian state
  return KeplerianElements{ central_body, t, a, e, i, o, w, v_final };
}

/*
Keplerian propagator methods
*/

// Direct constructor
KeplerianPropagator::KeplerianPropagator(KeplerianElements state) {
  this->initial_state = state;
}

// Propagate the inital state to specified epoch
ICRF KeplerianPropagator::propagate(UTCTime epoch) {
  return initial_state.propagate_to(epoch);
}