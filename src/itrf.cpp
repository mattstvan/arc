#include <data_files.h>
#include <earth_model.h>
#include <itrf.h>
#include <icrf.h>

/*
ITRF class methods
*/

// Default constructor (call base class)
ITRF::ITRF(){};

// Direct constructor
ITRF::ITRF(CelestialBody &body, DateTime &epoch, Vector3 &pos, Vector3 &vel)
    : Cartesian{body, epoch, pos, vel} {};

// Constructor from ICRF
ITRF::ITRF(ICRF &inertial) {
  // Get finals.all data
  std::array<double, 7> finals = DATA_FILES.get_finals(inertial.epoch.mjd());
  // Get rotation, precession and nutation values at epoch
  Vector3 rot = earth_rotation(inertial.epoch);
  std::array<double, 3> prec = earth_precession(inertial.epoch);
  std::array<double, 3> nutn = earth_nutation(inertial.epoch);
  double zeta = prec[0], theta = prec[1], zed = prec[2];
  double d_psi = nutn[0], d_eps = nutn[1], m_eps = nutn[2];
  // Rotate to MOD
  Vector3 r_mod = inertial.position.rot_z(-zeta).rot_y(theta).rot_z(-zed);
  Vector3 v_mod = inertial.velocity.rot_z(-zeta).rot_y(theta).rot_z(-zed);
  // Rotate to TOD
  double epsilon = d_eps + m_eps;
  Vector3 r_tod = r_mod.rot_x(m_eps).rot_z(-d_psi).rot_x(-epsilon);
  Vector3 v_tod = v_mod.rot_x(m_eps).rot_z(-d_psi).rot_x(-epsilon);
  // Rotate to PEF
  double ast = inertial.epoch.gmst_angle() + d_psi * cos(epsilon);
  Vector3 r_pef = r_tod.rot_z(ast);
  Vector3 v_arg = rot.inverse().cross(r_pef);
  Vector3 v_pef = v_tod.rot_z(ast).add(v_arg);
  // Rotate to ITRF
  double pm_x = finals[1], pm_y = finals[2];
  Vector3 r_itrf = r_pef.rot_x(-pm_y).rot_y(-pm_x);
  Vector3 v_itrf = v_pef.rot_x(-pm_y).rot_y(-pm_x);
  this->central_body = inertial.central_body;
  this->epoch = inertial.epoch;
  this->position = r_itrf;
  this->velocity = v_itrf;
}

// Print to std::cout
void ITRF::print() {
  std::cout << "[ITRF]" << std::endl;
  std::cout << " Central Body: ";
  central_body.print();
  std::cout << " Epoch: ";
  epoch.print();
  std::cout << " Position: ";
  position.print();
  std::cout << " Velocity: ";
  velocity.print();
}