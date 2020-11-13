#ifndef FILE_IO_H
#define FILE_IO_H
#include <fstream>
#include <string>
#include <vector>

/*
Write the given ASCII lines to file

@param lines Vector of strings to write to the file
@param filename Location in the filesystem at which to write the file
*/
void write_lines_to_file(std::vector<std::string> &lines, const char filename[]);

/*
Read ASCII lines from an existing file

@param filename Location in the filesystem of the ASCII file to be read
*/
std::vector<std::string> read_lines_from_file(const char filename[]);

#endif