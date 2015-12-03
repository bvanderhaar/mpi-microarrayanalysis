#include <stdio.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

std::string slurp(const std::string &filename) {
  std::ifstream in(filename, std::ifstream::in);
  std::stringstream sstr;
  sstr << in.rdbuf();
  std::string file = sstr.str();
  return file;
}

int main(int argc, char *argv[]) {
  int i = 0, current_row, current_col;
  std::string current_line, current_pos;
  int rows = 4551;
  int column_size = 63;
  // int array[][] = new int[rows][column size]
  std::vector<std::vector<std::string>> data(4551,
                                             std::vector<std::string>(63, ""));
  std::string source_data = slurp("NCI-60.csv");
  std::istringstream source_data_stream(source_data);

  for (current_row = 0; std::getline(source_data_stream, current_line);
       current_row++) {
    std::stringstream row_stream(current_line);
    for (current_col = 0; std::getline(row_stream, current_pos, ',');
         current_col++) {
      data[current_row][current_col] = current_pos;
    }
  }

  std::cout << "Printing last row: ";
  for (current_col = 0; current_col < column_size; current_col++) {
    std::cout << data[4550][current_col] << " ";
  }
  std::cout << std::endl;
}
