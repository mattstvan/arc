#include <body_propagation.h>
#include <cartesian.h>
#include <celestial.h>
#include <datetime.h>
#include <exceptions.h>

#include <sstream>

// Get the common name of a body by NAIF ID
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

// Get the CelestialBody static instance given its common name (i.e. "Mars")
CelestialBody get_body_by_name(std::string name) {
  // Convert string to uppercase
  for (char& c: name) {
    c = toupper(c);
  }
  if (name == "SUN") {
    return SUN;
  } else if (name == "MERCURY") {
    return MERCURY;
  } else if (name == "VENUS") {
    return VENUS;
  } else if (name == "EARTH") {
    return EARTH;
  } else if (name == "MOON" || name == "LUNA") {
    return LUNA;
  } else if (name == "MARS") {
    return MARS;
  } else if (name == "JUPITER") {
    return JUPITER;
  } else if (name == "SATURN") {
    return SATURN;
  } else if (name == "URANUS") {
    return URANUS;
  } else if (name == "NEPTUNE") {
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

// Get the body's common name
std::string CelestialBody::get_name() { return get_body_name(id); }

// Return the ratio between this body's polar and equatorial radii
double CelestialBody::flattening() {
  return (radius_equator - radius_polar) / radius_equator;
}

// Return the ratio between this body's polar and equatorial radii
double CelestialBody::j2() {
  double rot_mag = rotation.mag();
  double fltng = flattening();
  double j2 = (2.0*fltng/3.0) - (pow(radius_equator, 3)*pow(rot_mag, 2))/(3*mu);
  std::cout << j2 << std::endl;
  return j2;
}

// Obtain the ICRF state of this body at an epoch
ICRF CelestialBody::propagate(DateTime& epoch) {
  // Get the planet state from the body propagation handler
  return BODY_PROPAGATOR.get_state(id, epoch);
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