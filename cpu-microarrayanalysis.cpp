#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "BVshared.h"

int main(int argc, char *argv[]) {
  int current_row, current_col, rows = 4550, column_size = 63, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);

  /*for (current_row = 0; current_row < rows; current_row++) {
    for (current_col = 0; current_col < column_size; current_col++) {
    }
  }*/

  std::vector<double> renal;
  std::vector<double> normal;

  for (i = 0; i < 8; i++) {
    if (!vector[4549][i + 8].empty()) {
      std::cout << "Trying to convert " << vector[4549][i + 1] << " to double"
                << std::endl;
      renal.push_back(stod(vector[4549][i + 1]));
    }
  }
  for (i = 0; i < 60; i++) {
    if (!vector[4549][i + 8].empty()) {
      std::cout << "Trying to convert " << vector[4549][i + 8] << " to double"
                << std::endl;
      normal.push_back(stod(vector[4549][i + 8]));
    }
  }

  std::cout << "Renal Vector: ";
  print_1d_vector(renal);
  std::cout << "Normal Vector: ";
  print_1d_vector(normal);
  std::cout.precision(10);
  std::cout << "Renal Standard Deviation: " << standard_deviation(renal)
            << std::endl;
  std::cout << "Normal Standard Deviation: " << standard_deviation(normal)
            << std::endl;

  return 0;
}
