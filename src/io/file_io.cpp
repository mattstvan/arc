#include <exceptions.h>
#include <file_io.h>

#include <iomanip>
#include <istream>
#include <sstream>

// Write the given ASCII lines to file
void write_lines_to_file(std::vector<std::string> &lines,
                         const char filename[]) {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    for (std::string line : lines) {
      file << line << std::endl;
    }
    file.close();
  } else {
    std::stringstream msg;
    msg << "file_io::write_lines_to_file exception: Unable to write to '"
        << filename << "'";
    throw ArcException(msg.str());
  }
}

// Read ASCII lines from an existing file
std::vector<std::string> read_lines_from_file(const char filename[]) {
  std::ifstream file;
  file.open(filename);
  if (file.is_open()) {
    std::string line;
    std::vector<std::string> lines{};
    while (getline(file, line)) {
      lines.push_back(line);
    }
    return lines;
  } else {
    std::stringstream msg;
    msg << "file_io::read_lines_from_file exception: Unable to open '"
        << filename << "'";
    throw ArcException(msg.str());
  }
}

// Write the given JSON to file
void write_json_to_file(nlohmann::json json, const char filename[]) {
  std::ofstream out_file;
  out_file.open(filename);
  if (out_file.is_open()) {
    out_file << std::setw(4) << json << std::endl;
  } else {
    std::stringstream msg;
    msg << "file_io::write_json_to_file exception: Unable to open '" << filename
        << "'";
    throw ArcException(msg.str());
  }
}

// Read JSON from an existing file
nlohmann::json read_json_file(const char filename[]) {
  // Read file to stream
  std::ifstream in_file;
  in_file.open(filename);
  if (in_file.is_open()) {
    // Create JSON object
    nlohmann::json json;
    in_file >> json;
    return json;
  } else {
    std::stringstream msg;
    msg << "file_io::read_json_file exception: Unable to open '" << filename
        << "'";
    throw ArcException(msg.str());
  }
}