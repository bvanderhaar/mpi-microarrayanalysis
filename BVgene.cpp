#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

std::vector<gene_expression>
gene_expression_vector(std::vector<std::vector<std::string>> raw_data) {
  int current_row, current_col;
  double current_element;
  bool process = true;
  std::vector<gene_expression> gene_data;
  for (current_row = 1; current_row < raw_data.size(); current_row++) {
    gene_expression ge_row;
    ge_row.gene_name = raw_data[current_row][0];
    for (current_col = 0; current_col < raw_data[current_row].size();
         current_col++) {
      try {
        current_element = std::stod(raw_data[current_row][current_col]);
      } catch (std::exception &e) {
        process = false;
      }

      if (process) {
        if (current_col > 0 && current_col < 9) {
          ge_row.renal_disease.push_back(current_element);
        }
        if (current_col >= 9) {
          ge_row.control.push_back(current_element);
        }
      }
      process = true;
    }
    gene_data.push_back(ge_row);
  }
  return gene_data;
}

gene_result process(gene_expression data_row) {
  int i;
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
    // shuffle the order
    std::random_shuffle(all_gene_data.begin(), all_gene_data.end());
    // split the vector into 2
    std::vector<double> all_gene_data1(all_gene_data.begin(),
                                       all_gene_data.begin() +
                                           data_row.renal_disease.size()),
        all_gene_data2(all_gene_data.begin() + data_row.renal_disease.size(),
                       all_gene_data.end());
    // add the random t-stat to the t-stat list
    double random_t_stat = students_t_stat(all_gene_data1, all_gene_data2);
    permutation_t_stats.push_back(random_t_stat);
  }

  // find the d-score
  double t_stat = students_t_stat(data_row.renal_disease, data_row.control);
  double random_t_stat_mean = mean(permutation_t_stats);
  double random_standard_deviation = standard_deviation(permutation_t_stats);
  double absolute_value = std::abs(t_stat - random_t_stat_mean);
  double d_score = absolute_value / random_standard_deviation;
  return gene_result(data_row.gene_name, d_score);
}
