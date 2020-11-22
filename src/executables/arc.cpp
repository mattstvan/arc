#include <exceptions.h>
#include <run_config.h>

#include <iostream>

void print_help() {
  std::cout << std::endl << "Usage:" << std::endl
            << "arc [options] <file>" << std::endl
            << std::endl
            << "<file> must be a JSON file containing the run configuration "
               "for state propagation"
            << std::endl
            << std::endl
            << "Options: " << std::endl
            << " -help      Display this message" << std::endl
            << " -echo      Echo all messages to stdout" << std::endl;
}

int main(int argc, char* argv[]) {
  try {
    if (argc == 1) {
      throw ArcException("No run configuration file found.");
    } else if (std::string{argv[argc - 1]}.find("-help") != std::string::npos) {
      print_help();
      return 0;
    } else {
      // Run configuration file
      char* rc_filename = argv[argc - 1];
      run_config_file(rc_filename);
    }
  } catch (ArcException err) {
    std::cout << err.what() << std::endl;
    print_help();
    return 1;
  }
  return 0;
}