#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "BVshared.h"

struct gene_expression {
  std::string gene_name;
  std::vector<double> renal_disease;
  std::vector<double> control;
};

int main(int argc, char *argv[]) {
  int current_row, current_col, rows = 4550, column_size = 69, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);

  // the first element is a string of the gene name
  std::vector<gene_expression> gene_data(rows);
  /*for (current_row = 0; current_row < rows; current_row++) {
    for (current_col = 0; current_col < column_size; current_col++) {
    }
  }*/

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

  // combine vectors to do t-stat permutations
  std::vector<double> all_gene_data;
  all_gene_data.reserve(data_row.renal_disease.size() +
                        data_row.control.size()); // preallocate memory
  all_gene_data.insert(all_gene_data.end(), data_row.renal_disease.begin(),
                       data_row.renal_disease.end());
  all_gene_data.insert(all_gene_data.end(), data_row.control.begin(),
                       data_row.control.end());
  std::vector<double> permutation_t_stats;
  for (i = 0; i < 1000; i++) {
    // std::random_shuffle() permutation_t_stats.push_back()
  }

  std::cout << "Renal Vector: ";
  print_1d_vector(data_row.renal_disease);
  std::cout << "Normal Vector: ";
  print_1d_vector(data_row.control);
  std::cout.precision(10);
  std::cout << "Renal Standard Deviation: "
            << standard_deviation(data_row.renal_disease) << std::endl;
  std::cout << "Normal Standard Deviation: "
            << standard_deviation(data_row.control) << std::endl;
  std::cout << "Students T-Statistic: "
            << students_t_stat(data_row.renal_disease, data_row.control)
            << std::endl;

  return 0;
}
