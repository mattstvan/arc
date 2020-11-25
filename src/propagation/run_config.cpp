#include <celestial.h>
#include <datetime.h>
#include <ephemeris.h>
#include <exceptions.h>
#include <file_io.h>
#include <force_model.h>
#include <gravity.h>
#include <icrf.h>
#include <itrf.h>
#include <run_config.h>
#include <rungekutta4.h>
#include <vectors.h>

#include <sstream>

// Parse JSON representation of initial ICRF state
ICRF parse_state(nlohmann::json &json) {
  nlohmann::json state_json = json["INITIAL_STATE"];
  if (!state_json["CARTESIAN"].is_null()) {
    nlohmann::json state = state_json["CARTESIAN"];
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
    Vector3 pos{px, py, pz};
    Vector3 vel{vx, vy, vz};
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
      msg << "run_config::parse_state exception: Unsupported coordinate "
             "frame '"
          << frame << "'";
      throw ArcException(msg.str());
    }
  } else {
    // Throw error if state type is not recognized
    throw ArcException(
        "run_config::parse_state exception: Unsupported state type");
  }
}

// Parse JSON representation of force models
ForceModel parse_forces(nlohmann::json &prop) {
  ForceModel fm{};
  if (!prop["MODELS"].is_null()) {
    nlohmann::json models = prop["MODELS"];
    if (!models["GRAVITY"].is_null()) {
      nlohmann::json grav_models = models["GRAVITY"];
      for (nlohmann::json::iterator grav_model = grav_models.begin();
           grav_model != grav_models.end(); grav_model++) {
        CelestialBody grav_body = get_body_by_name(grav_model.key());
        // Gravity defaults
        bool grav_aspherical = false;
        int grav_deg = 0;
        int grav_order = 0;
        // Overwrite defaults if values exist
        nlohmann::json grav_settings = grav_model.value();
        if (!grav_settings["ASPHERICAL"].is_null()) {
          grav_aspherical = grav_settings["ASPHERICAL"];
        }
        if (!grav_settings["GEOPOTENTIAL_DEGREE"].is_null()) {
          grav_deg = grav_settings["GEOPOTENTIAL_DEGREE"];
        }
        if (!grav_settings["GEOPOTENTIAL_ORDER"].is_null()) {
          grav_order = grav_settings["GEOPOTENTIAL_ORDER"];
        }
        // Build gravity model and add it to the force model
        GravityModel gm{grav_body, grav_aspherical, grav_deg, grav_order};
        fm.add_gravity(gm);
      }
    }
  }
  return fm;
}

// Parse JSON representation of propagator options and build ephemeris
Ephemeris parse_propagate(nlohmann::json &prop, ICRF &state, ForceModel fm) {
  // Parse propagation start and stop times
  std::string start_str = prop["START_TIME"];
  std::string stop_str = prop["STOP_TIME"];
  DateTime start{start_str};
  DateTime stop{stop_str};
  // Create step variable
  double prop_step = 60;
  double int_step = 15;
  // Parse steps if given, otherwise leave at defaults
  if (!prop["PROPAGATION_STEP"].is_null()) {
    prop_step = prop["PROPAGATION_STEP"];
  }
  if (!prop["INTEGRATION_STEP"].is_null()) {
    int_step = prop["INTEGRATION_STEP"];
  }
  // Determine method of propagation and create the ephemeris
  if (!prop["METHOD"].is_null()) {
    if (prop["METHOD"] == "RK4") {
      RungeKutta4 propagator{state, int_step, fm};
      return propagator.step(start, stop, prop_step);
    } else {
      throw ArcException(
          "run_config::run_config_file exception: Unknown "
          "propagation method selected");
    }
  } else {
    throw ArcException(
        "run_config::run_config_file exception: No propagation "
        "method selected");
  }
}

// Take the resulting trajectory from the run and produce requested products
void post_process(Ephemeris ephem, nlohmann::json output) {
  if (!output.is_null()) {
    if (!output["EPHEMERIS"].is_null()) {
      nlohmann::json ephem_json = output["EPHEMERIS"];
      std::string filename = "arc.out";
      if (!ephem_json["FILENAME"].is_null()) {
        filename = ephem_json["FILENAME"];
      }
      if (!ephem_json["FORMAT"].is_null()) {
        if (ephem_json["FORMAT"] == "STK") {
          ephem.write_stk(filename.c_str());
        }
      } else {
        ephem.write_stk(filename.c_str());
      }
    }
  } else {
    throw ArcException(
        "run_config::post_process exception: No output product types");
  }
}


// Execute a run task using a run configuration file
void run_config_file(const char filepath[]) {
  try {
    // Read in JSON file
    nlohmann::json json = read_json_file(filepath);
    // Get conditions file sections
    nlohmann::json input = json["ARC_RUN"]["INPUT"];
    nlohmann::json prop = json["ARC_RUN"]["PROPAGATION"];
    nlohmann::json output = json["ARC_RUN"]["OUTPUT"];
    ICRF initial_state = parse_state(input);
    ForceModel fm = parse_forces(prop);
    Ephemeris ephem = parse_propagate(prop, initial_state, fm);
    post_process(ephem, output);
  } catch (ArcException err) {
    std::cout << err.what() << std::endl;
    std::stringstream msg;
    msg << "InitialConditions constructor exception: Error parsing initial "
        << "conditions file'" << filepath << "'";
    throw ArcException(msg.str());
  }
}