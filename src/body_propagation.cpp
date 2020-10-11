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