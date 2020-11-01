#ifndef FILE_IO_H
#define FILE_IO_H
#include <fstream>
#include <string>
#include <vector>

// Write the given ASCII lines to file
void write_lines_to_file(std::vector<std::string> &lines, char filename[]);

// Read ASCII lines from an existing file
std::vector<std::string> read_lines_from_file(char filename[]);

#endif