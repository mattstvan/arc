#include <body_propagation.h>
#include <cartesian.h>
#include <celestial.h>
#include <datetime.h>
#include <exceptions.h>

#include <sstream>

/*
Get the common name of a body by NAIF ID

@param id NAIF ID number of the body
@returns (std::string) Common name of the given body
@throws exceptions::ArcException if ID is not known
*/
std::string get_body_name(int id) {
  switch (id) {
    case 10:
      return std::string{"Sun"};
    case 199:
      return std::string{"Mercury"};
    case 299:
      return std::string{"Venus"};
    case 399:
      return std::string{"Earth"};
    case 301:
      return std::string{"Luna"};
    case 499:
      return std::string{"Mars"};
    case 599:
      return std::string{"Jupiter"};
    case 699:
      return std::string{"Saturn"};
    case 799:
      return std::string{"Uranus"};
    case 899:
      return std::string{"Neptune"};
    default:
      std::stringstream msg;
      msg << "celestial::get_body_name exception: No common name available for "
             "NAIF ID "
          << id;
      throw ArcException(msg.str());
  }
};

/*
Get the CelestialBody static instance given its common name (i.e. "Mars")

@param name The common name of the requested body
@returns (celestial::CelestialBody) The static instance of the requested body
@throws exceptions::ArcException if name is not known
*/
CelestialBody get_body_by_name(std::string name) {
  if (name == "Sun") {
    return SUN;
  } else if (name == "Mercury") {
    return MERCURY;
  } else if (name == "Venus") {
    return VENUS;
  } else if (name == "Earth") {
    return EARTH;
  } else if (name == "Moon") {
    return LUNA;
  } else if (name == "Mars") {
    return MARS;
  } else if (name == "Jupiter") {
    return JUPITER;
  } else if (name == "Saturn") {
    return SATURN;
  } else if (name == "Uranus") {
    return URANUS;
  } else if (name == "Neptune") {
    return NEPTUNE;
  } else {
    std::stringstream msg;
    msg << "celestial::get_body_by_name exception: '" << name
        << "' is not defined";
    throw ArcException(msg.str());
  }
};

/*
Celestial body methods
*/

/*
Obtain the ICRF state of this body at an epoch

@param epoch The requested time at which to obtain the ICRF state
@returns (icrf::ICRF) The calculated state at the requested epoch
*/
ICRF CelestialBody::propagate(DateTime& epoch) {
  // Get the planet state from the body propagation handler
  return BODY_PROPAGATOR.get_state(id, epoch);
}

/*
Get the body's common name

@returns (std::string) Common name of this body
*/
std::string CelestialBody::get_name() { return get_body_name(id); }

/*
Return the ratio between this body's polar and equatorial radii, calculated as 1
- (r_p/r_e)

@returns (double) Flattening ratio of this body
*/
double CelestialBody::flattening_ratio() {
  return 1 - (radius_polar / radius_equator);
}

/*
CelestialBody operator functions
*/

// I/O stream
std::ostream& operator<<(std::ostream& out, CelestialBody& body) {
  out << "[CelestialBody] { ID: " << body.id << ", Name: " << body.get_name()
      << " }";
  return out;
}