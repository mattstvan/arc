#include <ephemeris.h>
#include <file_io.h>

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
Ephemeris::Ephemeris(std::vector<ICRF> states) {
  this->states = states;
  this->epoch = states[0].epoch;
  this->central_body = states[0].central_body;
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
  // Create the vector of lines and write the header
  std::vector<std::string> lines;
  lines.push_back(std::string{"stk.v.11.0"});
  lines.push_back(std::string{"# WrittenBy Arc"});
  lines.push_back(std::string{"BEGIN Ephemeris"});

  // Number of ephemeris points line
  std::stringstream n_points;
  n_points << "NumberOfEphemerisPoints " << states.size();
  lines.push_back(n_points.str());

  // Scenario epoch line
  std::stringstream epoch_str;
  epoch_str << "ScenarioEpoch " << epoch.format_fractional("%d %b %Y %H:%M:%S");
  lines.push_back(epoch_str.str());

  // Central body line
  std::stringstream body_str;
  body_str << "CentralBody " << central_body.get_name();
  lines.push_back(body_str.str());

  // Build the ephemeris points
  lines.push_back("CoordinateSystem ICRF");
  lines.push_back("EphemerisTimePosVel");

  // For each state in the state list
  for (ICRF state : states) {
    // Calculate time since epoch
    double tplus = state.epoch.difference(epoch);

    // Stream t+, rx, ry, rz, vx, vy, vz into each line
    std::stringstream point_line;
    point_line << std::setprecision(14);
    point_line << std::scientific << tplus << " " << state.position.x << " "
               << state.position.y << " " << state.position.z << " "
               << state.velocity.x << " " << state.velocity.y << " "
               << state.velocity.z;

    // Add the line to the lines vector
    lines.push_back(point_line.str());
  }

  lines.push_back("END Ephemeris");
  return lines;
}

// Write ephemeris to file using STK format
void Ephemeris::write_stk(char filename[]) {
  int result = write_lines_to_file(format_stk(), filename);
  if (result == 1) {
    std::cout << "Unable to write Ephemeris to file location: " << filename
              << std::endl;
  }
}