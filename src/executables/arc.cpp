#include <exceptions.h>
#include <initial_conditions.h>

#include <iostream>

void print_help() {
  std::cout << std::endl << "Usage:" << std::endl
            << "arc [options] <file>" << std::endl
            << std::endl
            << "<file> must be a JSON file containing the initial conditions "
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
      throw ArcException("No initial conditions file found.");
    } else if (std::string{argv[argc - 1]}.find("-help") != std::string::npos) {
      print_help();
      return 0;
    } else {
      // Initial conditions file
      char* ic_filename = argv[argc - 1];
      InitialConditions ic {ic_filename};
    }
  } catch (ArcException err) {
    std::cout << err.what() << std::endl;
    print_help();
    return 1;
  }
  return 0;
}