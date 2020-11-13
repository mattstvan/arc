#include <data_files.h>
#include <earth_model.h>
#include <icrf.h>
#include <itrf.h>

/*
ICRF class methods
*/

/*
Default constructor

Calls the base Cartesian default constructor
*/
ICRF::ICRF() {};

/*
Direct constructor

@param body (celestial::CelestialBody) Body at the center of this coordinate
system
@param epoch (datetime::DateTime) epoch at which these coordinates are valid
@param pos (vectors::Vector3) position vector of the state in meters
@param vel (vectors::Vector3) velocity vector of the state in meters per second
*/
ICRF::ICRF(CelestialBody& body, DateTime& epoch, Vector3& pos, Vector3& vel)
  : Cartesian{ body, epoch, pos, vel } {};

/*
Constructor from ITRF

Rotates an ITRF (Earth-centered, Earth-fixed) state into Earth-centered ICRF

@param fixed ITRF state to rotate into ICRF
*/
ICRF::ICRF(ITRF& fixed) {
  // Get finals.all data
  std::array<double, 7> finals = DATA_FILES.get_finals(fixed.epoch.mjd());
  double pm_x = finals[1], pm_y = finals[2];
  // Get rotation, precession and nutation values at epoch
  Vector3 rot = earth_rotation(fixed.epoch);
  std::array<double, 3> prec = earth_precession(fixed.epoch);
  std::array<double, 3> nutn = earth_nutation(fixed.epoch);
  double zeta = prec[0], theta = prec[1], zed = prec[2];
  double d_psi = nutn[0], d_eps = nutn[1], m_eps = nutn[2];
  double epsilon = d_eps + m_eps;
  // Rotate to PEF
  Vector3 r_pef = fixed.position.rot_y(pm_x).rot_x(pm_y);
  Vector3 v_pef = fixed.velocity.rot_y(pm_x).rot_x(pm_y);
  // Rotate to TOD
  double ast = fixed.epoch.gmst_angle() + d_psi * cos(epsilon);
  Vector3 r_tod = r_pef.rot_z(-ast);
  Vector3 v_arg = rot.cross(r_pef);
  Vector3 v_tod = v_pef.add(v_arg).rot_z(-ast);
  // Rotate to MOD
  Vector3 r_mod = r_tod.rot_x(epsilon).rot_z(d_psi).rot_x(-m_eps);
  Vector3 v_mod = v_tod.rot_x(epsilon).rot_z(d_psi).rot_x(-m_eps);
  // Rotate to ICRF
  Vector3 r_icrf = r_mod.rot_z(zed).rot_y(-theta).rot_z(zeta);
  Vector3 v_icrf = v_mod.rot_z(zed).rot_y(-theta).rot_z(zeta);
  this->central_body = fixed.central_body;
  this->epoch = fixed.epoch;
  this->position = r_icrf;
  this->velocity = v_icrf;
}

/*
Constructor from KeplerianElements

Builds a cartesian ICRF state from ICRF keplerian elements

@param el Keplerian elements from which to build the state
*/
ICRF::ICRF(KeplerianElements& el) : Cartesian{ el } {};

/*
Convert position/velocity vectors into the sun-centered ICRF frame

@returns This state in heliocentric ICRF
*/
ICRF ICRF::to_solar() {
  // If this state is not already heliocentric
  if (central_body.id != 10) {
    // This call will be recursive until we find a solar state
    ICRF body_icrf = central_body.propagate(epoch).to_solar();
    // Add the body's heliocentric state to this state and return
    Vector3 solar_pos = body_icrf.position.add(position);
    Vector3 solar_vel = body_icrf.velocity.add(velocity);
    return ICRF{ SUN, epoch, solar_pos, solar_vel };
  }
  else {
    // If this state is already heliocentric, return a copy
    return ICRF{ central_body, epoch, position, velocity };
  }
}

/*
Convert position/velocity vectors into the ICRF frame centered around another
celestial body's position

@param body Celestial body around which to center the new state
*/
ICRF ICRF::change_central_body(CelestialBody& body) {
  // If the requested body does differ
  if (central_body.id != body.id) {
    // If the requested body is the Sun
    if (body.id == 10) {
      return to_solar();
    }
    // Get both states in heliocentric ICRF
    ICRF body_icrf = body.propagate(epoch).to_solar();
    ICRF solar_icrf = to_solar();
    // Change the origin of this position and velocity to the other body
    Vector3 new_pos = solar_icrf.position.change_origin(body_icrf.position);
    Vector3 new_vel = solar_icrf.velocity.change_origin(body_icrf.velocity);
    // Return the new ICRF state
    return ICRF{ body, epoch, new_pos, new_vel };
  }
  else {
    // If this state's central body is already the one requested, return a copy

    return ICRF{ central_body, epoch, position, velocity };
  }
}

/*
ICRF operator functions
*/

// I/O stream 
std::ostream& operator << (std::ostream& out, ICRF& icrf) {
  out << "[ICRF]" << std::endl << " Central Body: " << icrf.central_body << std::endl
    << " Epoch: " << icrf.epoch << std::endl << " Position: " << icrf.position << std::endl
    << " Velocity: " << icrf.velocity;
  return out;
}