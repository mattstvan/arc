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
        default:
            return std::string("Unknown");
    }
};

/*
Celestial body methods
*/

// Print to std::cout
void CelestialBody::print() {
    std::cout << "[CelestialBody]\n ID: " << id << "\n Name: " << get_name() << std::endl;
}

// Return the common name of the body as a String
std::string CelestialBody::get_name() {
    return get_body_name(id);
}