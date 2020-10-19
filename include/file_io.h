#ifndef FILE_IO_H
#define FILE_IO_H
#include <fstream>
#include <string>
#include <vector>

int write_lines_to_file(std::vector<std::string> &lines, char filename[]);

std::vector<std::string> read_lines_from_file(char filename[]);

#endif