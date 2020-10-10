#include <ephemeris.h>

#include <iostream>
#include <sstream>
#include <iomanip>

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
  lines.push_back(std::string{"# WrittenBy Arc"});
  lines.push_back(std::string{"BEGIN Ephemeris"});
  std::stringstream n_points;
  n_points << "NumberOfEphemerisPoints " << states.size();
  lines.push_back(n_points.str());
  std::stringstream epoch_str;
  epoch_str << "ScenarioEpoch " << epoch.format_fractional("%d %b %Y %H:%M:%S");
  lines.push_back(epoch_str.str());
  std::stringstream body_str;
  body_str << "CentralBody " << central_body.get_name();
  lines.push_back(body_str.str());
  lines.push_back("CoordinateSystem ICRF");
  lines.push_back("EphemerisTimePosVel");
  for (ICRF state : states) {
    double tplus = state.epoch.difference(epoch);
    std::stringstream point_line;
    point_line << std::setprecision(14);
    point_line << std::scientific << tplus << " " << state.position.x << " " << state.position.y
               << " " << state.position.z << " " << state.velocity.x << " "
               << state.velocity.y << " " << state.velocity.z;
    lines.push_back(point_line.str());
  }
  lines.push_back("END Ephemeris");
  return lines;
}