#include <ephemeris.h>
#include <iostream>

/*
Ephemeris class methods
*/

// Default constructor
Ephemeris::Ephemeris() {
  this->states = std::vector<ICRF>{};
  this->epoch = UTCTime{};
  this->central_body = SUN;
}

// Direct constructor
Ephemeris::Ephemeris(std::vector<ICRF> states, UTCTime epoch,
                     CelestialBody body) {
  this->states = states;
  this->epoch = epoch;
  this->central_body = body;
}

// Print to std::cout
void Ephemeris::print() {
  std::cout << "[Ephemeris] { Epoch: " << epoch.to_iso()
            << ", Number of states: " << states.size()
            << ", Central body: " << central_body.get_name() << " }"
            << std::endl;
}

// Create ASCII ephemeris in STK format (.e)
std::vector<std::string> Ephemeris::format_stk() {
  std::vector<std::string> lines;
  lines.push_back(std::string{"stk.v.11.0"});

  return lines;
}