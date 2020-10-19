#include <ephemeris.h>
#include <cstdio>

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

// Constructor using file path
Ephemeris::Ephemeris(char filepath[]) {
  this->central_body = SUN;
  this->epoch = UTCTime{};
  this->states = std::vector<ICRF>{};
  std::vector<std::string> lines = read_lines_from_file(filepath);
  if (lines.size() > 0) {
    bool ephem_section = false;
    for (std::string line : lines) {
      // Check for epoch
      if (line.find("ScenarioEpoch") != std::string::npos) {
        std::string datestr = line.substr(line.find("ScenarioEpoch") + 14, line.size() - 1);
        if (datestr.size() > 0) {
          this->epoch = UTCTime{ datestr, "%d %b %Y %H:%M:%S" };
        }
        // Check for central body
      }
      else if (line.find("CentralBody") != std::string::npos) {
        std::string bodystr = line.substr(line.find("CentralBody") + 12, line.size() - 1);
        this->central_body = get_body_by_name(bodystr);
      }
      else if (line.find("END Ephemeris") != std::string::npos) {
        ephem_section = false;
      }
      else if (ephem_section == true) {
        // Parse a state
        float tplus, x, y, z, vx, vy, vz;
        sscanf(line.c_str(), "%f %f %f %f %f %f %f", &tplus, &x, &y, &z, &vx, &vy, &vz);
        UTCTime new_epoch = epoch.increment(tplus);
        states.push_back(ICRF{ central_body, new_epoch, Vector3{x, y, z}, Vector3 {vx, vy, vz} });
      }
      else if (line.find("EphemerisTimePosVel") != std::string::npos) {
        // Begin parsing states
        ephem_section = true;
      }
    }
  }

}

// Print to std::cout
void Ephemeris::print() {
  std::cout << "[Ephemeris] { Epoch: " << epoch.to_iso()
    << ", Number of states: " << states.size()
    << ", Central body: " << central_body.get_name() << " }"
    << std::endl;
}

// Use Keplerian estimation to obtain an interpolated ICRF
// state using the nearest ICRF value contained in the ephemeris
ICRF Ephemeris::interpolate(UTCTime requested) {
  // Single call to get number of states (for performance)
  int ephem_size = states.size();
  // Nearest (by epoch) state to requested time
  ICRF nearest = states[0];
  // If requested time is after last state
  if (requested.difference(states[ephem_size - 1].epoch) >= 0.0) {
    // Set nearest to the last available state
    nearest = states[ephem_size - 1];
    // If requested time is before first state
  } else if (requested.difference(states[0].epoch) <= 0.0) {
    // Set nearest to the first available state
    nearest = states[0];
  } else {
    // Find the total time span of the available states
    double span_sec = states[ephem_size-1].epoch.difference(states[0].epoch);
    // Find the expected number of seconds into the ephemeris the requested epoch is
    double expected_sec = requested.difference(states[0].epoch);
    // Expected percentage into the total ephemeris span
    double expected_per = expected_sec / span_sec;
    // Estimated index in ephemeris
    int est_index = (int)(ephem_size * expected_per);
    nearest = states[est_index];
  }
  // Convert the nearest state to keplerian
  KeplerianElements nearest_keplerian{ nearest };
  // Propagate the keplerian state to the requested time and return the result
  // in ICRF
  return ICRF{ nearest_keplerian.propagate_to(requested) };
}

// Create ASCII ephemeris in STK format (.e)
std::vector<std::string> Ephemeris::format_stk() {
  // Create the vector of lines and write the header
  std::vector<std::string> lines;
  lines.push_back(std::string{ "stk.v.11.0" });
  lines.push_back(std::string{ "# WrittenBy Arc" });
  lines.push_back(std::string{ "BEGIN Ephemeris" });

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