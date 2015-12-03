#include <stdio.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

std::string slurp(const std::string &filename) {
  std::ifstream in(filename, std::ifstream::in);
  std::stringstream sstr;
  sstr << in.rdbuf();
  std::string file = sstr.str();
  return file;
}

int main(int argc, char *argv[]) {
  std::string source_data = slurp("NCI-60.csv");
  std::istringstream source_data_stream(source_data);
  for (std::string line; std::getline(source_data_stream, line);) {
    std::cout << ">> " + line + "\n";
  }
}
