#ifndef FILE_IO_H
#define FILE_IO_H
#include <fstream>
#include <string>
#include <vector>

int write_lines_to_file(std::vector<std::string> lines, char filename[]) {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    for (std::string line : lines) {
      file << line << std::endl;
    }
    file.close();
    return 0;
  } else {
    return 1;
  }
}

#endif