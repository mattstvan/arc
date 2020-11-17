#include <celestial.h>
#include <datetime.h>
#include <exceptions.h>
#include <file_io.h>
#include <icrf.h>
#include <initial_conditions.h>
#include <itrf.h>
#include <vectors.h>

#include <sstream>

// Parse JSON representation to initial ICRF state
ICRF parse_state(nlohmann::json &json) {
  if (!json["CARTESIAN"].is_null()) {
    nlohmann::json state = json["CARTESIAN"];
    // Parse central body
    std::string body_str = state["CENTRAL_BODY"];
    CelestialBody body = get_body_by_name(body_str);
    // Parse epoch
    std::string dt_str = state["EPOCH"];
    DateTime epoch{dt_str};
    // Parse cartesian components
    double px = state["POSITION"]["X"];
    double py = state["POSITION"]["Y"];
    double pz = state["POSITION"]["Z"];
    double vx = state["VELOCITY"]["X"];
    double vy = state["VELOCITY"]["Y"];
    double vz = state["VELOCITY"]["Z"];
    Vector3 pos {px, py, pz};
    Vector3 vel {vx, vy, vz};
    // Determine coordinate frame
    std::string frame = state["FRAME"];
    if (frame == "ICRF" || frame == "J2000" || frame == "ECI") {
      // Construct directly if ICRF or J2000 is stated
      return ICRF{body, epoch, pos, vel};
    } else if (frame == "ITRF" || frame == "ECF") {
      // Rotate to Earth-centered ICRF if ITRF is stated
      ITRF itrf{EARTH, epoch, pos, vel};
      return ICRF{itrf};
    } else {
      // Throw error if frame is not recognized
      std::stringstream msg;
      msg << "InitialConditions parse_state exception: Unsupported coordinate "
             "frame '"
          << frame << "'";
      throw ArcException(msg.str());
    }
  } else {
    // Throw error if state type is not recognized
    throw ArcException(
        "InitialConditions parse_state exception: Unsupported state type");
  }
}

// Constructor from JSON file
InitialConditions::InitialConditions(const char filepath[]) {
  try {
    // Read in JSON file
    nlohmann::json json = read_json_file(filepath);
    // Get conditions file sections
    nlohmann::json input = json["ARC_INITIAL_CONDITIONS"]["INPUT"];
    nlohmann::json prop = json["ARC_INITIAL_CONDITIONS"]["PROPAGATION"];
    nlohmann::json output = json["ARC_INITIAL_CONDITIONS"]["OUTPUT"];
    ICRF initial_state = parse_state(input["INITIAL_STATE"]);
    std::cout << initial_state << std::endl;
  } catch (ArcException err) {
    std::cout << err.what() << std::endl;
    std::stringstream msg;
    msg << "InitialConditions constructor exception: Error parsing initial "
        << "conditions file'" << filepath << "'";
    throw ArcException(msg.str());
  }
}

/*
InitialConditions operator functions
*/

// I/O stream
std::ostream &operator<<(std::ostream &out, InitialConditions &ic) {
  out << "[InitialConditions]";
  return out;
}