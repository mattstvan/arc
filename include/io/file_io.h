#ifndef FILE_IO_H
#define FILE_IO_H
#include <fstream>
#include <string>
#include <vector>
#include <json.h>

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

/*
Write the given JSON to file

@param json JSON object to write
@param filename Location in the filesystem at which to write the file
*/
void write_lines_to_file(nlohmann::json json, const char filename[]);

/*
Read JSON from an existing file

@param filename Location in the filesystem of the JSON file to be read
*/
nlohmann::json read_json_file(const char filename[]);



#endif