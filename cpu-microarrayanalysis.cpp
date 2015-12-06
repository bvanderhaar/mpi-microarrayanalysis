#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

int main(int argc, char *argv[]) {
  int current_row, current_col, rows = 4550, column_size = 69, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);

  // the first element is a string of the gene name
  std::vector<gene_expression> gene_data(rows);

  current_row = 4549;
  gene_expression data_row;
  data_row.gene_name = vector[current_row][0];
  for (i = 0; i < 8; i++) {
    if (!vector[current_row][i + 1].empty()) {
      data_row.renal_disease.push_back(stod(vector[4549][i + 1]));
    }
  }
  for (i = 0; i < 60; i++) {
    if (!vector[current_row][i + 8].empty()) {
      data_row.control.push_back(stod(vector[4549][i + 8]));
    }
  }

  gene_result result = process(data_row);

  // std::cout << "Renal Vector: ";
  // print_1d_vector(data_row.renal_disease);
  // std::cout << "Normal Vector: ";
  // print_1d_vector(data_row.control);
  std::cout.precision(10);
  /*std::cout << "Renal Standard Deviation: "
            << standard_deviation(data_row.renal_disease) << std::endl;
  std::cout << "Normal Standard Deviation: "
            << standard_deviation(data_row.control) << std::endl;
  std::cout << "Students T-Statistic: "
            << students_t_stat(data_row.renal_disease, data_row.control)
            << std::endl; */
  std::cout << "Gene Name: " << result.gene_name << std::endl;
  std::cout << "D-Score: " << result.d_score << std::endl;

  return 0;
}
