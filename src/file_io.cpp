#include <file_io.h>

int write_lines_to_file(std::vector<std::string> &lines, char filename[]) {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    for (std::string line : lines) {
      file << line << std::endl;
    }
    file.close();
    return 0;
  }
  else {
    return 1;
  }
}

std::vector<std::string> read_lines_from_file(char filename[]) {
  std::ifstream file;
  file.open(filename);
  if (file.is_open()) {
    std::string line;
    std::vector<std::string> lines{};
    while (getline(file, line)) {
      lines.push_back(line);
    }
    return lines;
  }
  else {
    return std::vector<std::string> {};
  }
}