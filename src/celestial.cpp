#include <cartesian.h>
#include <celestial.h>
#include <datetime.h>
#include <body_propagation.h>
#include <exceptions.h>
#include <sstream>

// Return the common name of a body by NAIF ID
std::string get_body_name(int id) {
  switch (id) {
  case 10:
    return std::string{ "Sun" };
  case 199:
    return std::string{ "Mercury" };
  case 299:
    return std::string{ "Venus" };
  case 399:
    return std::string{ "Earth" };
  case 301:
    return std::string{ "Luna" };
  case 499:
    return std::string{ "Mars" };
  case 599:
    return std::string{ "Jupiter" };
  case 699:
    return std::string{ "Saturn" };
  case 799:
    return std::string{ "Uranus" };
  case 899:
    return std::string{ "Neptune" };
  default:
    std::stringstream msg;
    msg << "celestial::get_body_name exception: No common name available for NAIF ID " << id;
    throw ArcException(msg.str());
  }
};

// Return the CelestialBody given a common name (i.e. "Mars")
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
  } else {
    std::stringstream msg;
    msg << "celestial::get_body_by_name exception: '" << name  << "' is not defined";
    throw ArcException(msg.str());
  }
};

/*
Celestial body methods
*/

// Return the ICRF state of the body at an epoch
ICRF CelestialBody::propagate(DateTime &epoch) {
  // Get the planet state from the body propagation handler
  return BODY_PROPAGATOR.get_state(id, epoch);
}

// Print to std::cout
void CelestialBody::print() {
  std::cout << "[CelestialBody] { ID: " << id << ", Name: " << get_name()
    << " }" << std::endl;
}

// Return the common name of the body as a String
std::string CelestialBody::get_name() { return get_body_name(id); }