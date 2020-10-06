#include <iostream>
#include <string>
#include <celestial.h>

// Return the common name of a body by NAIF ID
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
        default:
            return std::string("Unknown");
    }
};

/*
Celestial body methods
*/

// Print to std::cout
void CelestialBody::print() {
    std::cout << "[CelestialBody] { ID: " << id << ", Name: " << get_name() << " }" << std::endl;
}

// Return the common name of the body as a String
std::string CelestialBody::get_name() {
    return get_body_name(id);
}