#include <body_propagation.h>

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

// Get and/or load a planetary ephemeris file
Ephemeris& BodyPropagationHandler::get_ephem(int id) {
    // TODO: Functionally determine ephemeris location
    // Use temporary ephemeris file locations (will be set by variable later)
    switch (id) {
    case 199:
        if (mercury.states.size() == 0) {
            mercury = Ephemeris{ "data/planetary/mercury.txt" };
        }
        return mercury;
    case 299:
        if (venus.states.size() == 0) {
            venus = Ephemeris{ "data/planetary/venus.txt" };
        }
        return venus;
    case 399:
        if (earth.states.size() == 0) {
            earth = Ephemeris{ "data/planetary/earth.txt" };
        }
        return earth;
    case 301:
        if (luna.states.size() == 0) {
            luna = Ephemeris{ "data/planetary/luna.txt" };
        }
        return luna;
    case 499:
        if (mars.states.size() == 0) {
            mars = Ephemeris{ "data/planetary/mars.txt" };
        }
        return mars;
    case 599:
        if (jupiter.states.size() == 0) {
            jupiter = Ephemeris{ "data/planetary/jupiter.txt" };
        }
        return jupiter;
    case 699:
        if (saturn.states.size() == 0) {
            saturn = Ephemeris{ "data/planetary/saturn.txt" };
        }
        return saturn;
    case 799:
        if (uranus.states.size() == 0) {
            uranus = Ephemeris{ "data/planetary/uranus.txt" };
        }
        return uranus;
    case 899:
        if (neptune.states.size() == 0) {
            neptune = Ephemeris{ "data/planetary/neptune.txt" };
        }
        return neptune;
    }
}

// Get the state of a given CelestialBody given its NAIF ID
ICRF BodyPropagationHandler::get_state(int id, UTCTime &epoch) {
    // If the body is not the Sun
    if (id != 10) {
        Ephemeris& planet_eph = get_ephem(id);
        return planet_eph.interpolate(epoch);
    }
    else {
        // If it is the sun, return the system origin at the requested time
        return ICRF{SUN, epoch, Vector3{}, Vector3{}};
    }
}