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

std::vector<std::vector<std::string>> vectorize(std::string filename, int rows,
                                                int column_size) {
  int current_row, current_col;
  std::string current_line, current_pos;
  std::vector<std::vector<std::string>> data(
      rows, std::vector<std::string>(column_size, ""));
  std::string source_data = slurp(filename);
  std::istringstream source_data_stream(source_data);
  for (current_row = 0; std::getline(source_data_stream, current_line);
       current_row++) {
    std::stringstream row_stream(current_line);
    for (current_col = 0; std::getline(row_stream, current_pos, ',');
         current_col++) {
      data[current_row][current_col] = current_pos;
    }
  }
  return data;
}

int main(int argc, char *argv[]) {
  int current_col, rows = 4550, column_size = 63;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);
  std::cout << "Printing last row: ";
  for (current_col = 0; current_col < column_size; current_col++) {
    std::cout << vector[4549][current_col] << " ";
  }
  std::cout << std::endl;
}
