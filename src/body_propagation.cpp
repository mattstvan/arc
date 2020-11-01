#include <body_propagation.h>
#include <exceptions.h>

#include <iostream>
#include <sstream>

/*
Body propagation handler methods
*/

// Default constructor
BodyPropagationHandler::BodyPropagationHandler() {
  this->mercury = Ephemeris{};
  this->venus = Ephemeris{};
  this->earth = Ephemeris{};
  this->mars = Ephemeris{};
  this->jupiter = Ephemeris{};
  this->saturn = Ephemeris{};
  this->uranus = Ephemeris{};
  this->neptune = Ephemeris{};
}

/*
Returns a planetary ephemeris file, loading it from disk if necessary

@param id NAIF id of the requested celestial body
@returns ephemeris::Ephemeris instance of the requested celestial body
@throws exceptions::ArcException if ephemeris file is not found
*/
Ephemeris& BodyPropagationHandler::get_ephem(int id) {
  // TODO: Functionally determine ephemeris location
  // Use temporary ephemeris file locations (will be set by variable later)
  switch (id) {
    case 199:
      if (mercury.states.size() == 0) {
        mercury = Ephemeris{"data/planetary/mercury.txt"};
      }
      return mercury;
    case 299:
      if (venus.states.size() == 0) {
        venus = Ephemeris{"data/planetary/venus.txt"};
      }
      return venus;
    case 399:
      if (earth.states.size() == 0) {
        earth = Ephemeris{"data/planetary/earth.txt"};
      }
      return earth;
    case 301:
      if (luna.states.size() == 0) {
        luna = Ephemeris{"data/planetary/luna.txt"};
      }
      return luna;
    case 499:
      if (mars.states.size() == 0) {
        mars = Ephemeris{"data/planetary/mars.txt"};
      }
      return mars;
    case 599:
      if (jupiter.states.size() == 0) {
        jupiter = Ephemeris{"data/planetary/jupiter.txt"};
      }
      return jupiter;
    case 699:
      if (saturn.states.size() == 0) {
        saturn = Ephemeris{"data/planetary/saturn.txt"};
      }
      return saturn;
    case 799:
      if (uranus.states.size() == 0) {
        uranus = Ephemeris{"data/planetary/uranus.txt"};
      }
      return uranus;
    case 899:
      if (neptune.states.size() == 0) {
        neptune = Ephemeris{"data/planetary/neptune.txt"};
      }
      return neptune;
    default:
      std::stringstream msg;
      msg << "BodyPropagator::get_ephem exception: No ephemeris found for NAIF "
             "id "
          << id;
      throw ArcException(msg.str());
  }
}

/*
Get the state of a given CelestialBody given its NAIF ID

@param id NAIF id of the requested celestial body
@param epoch Requested time to which to compute an ICRF state
@returns icrf::ICRF instance representing requested body at requested time
@throws exceptions::ArcException if ephemeris file is not found or propagation
fails
*/
ICRF BodyPropagationHandler::get_state(int id, DateTime& epoch) {
  // If the body is not the Sun
  if (id != 10) {
    try {
      // Get reference to loaded ephemeris
      Ephemeris& planet_eph = get_ephem(id);
      // Return interpolated state at epoch
      return planet_eph.interpolate(epoch);
    } catch (ArcException err) {
      std::cout << err.what() << std::endl;
      throw ArcException(
          "BodyPropagator::get_state exception: Propagation of CelestialBody "
          "failed");
    }
  } else {
    // If it is the sun, return the system origin at the requested time
    Vector3 pos_origin;
    Vector3 vel_origin;
    return ICRF{SUN, epoch, pos_origin, vel_origin};
  }
}