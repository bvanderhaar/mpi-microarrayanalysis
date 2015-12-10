#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "BVshared.h"
#include "BVgene.h"

std::map<int, std::string>
gene_index(std::vector<gene_expression> gene_expression_vector) {
  std::map<int, std::string> gene_index_data;
  for (int i = 0; i < gene_expression_vector.size(); i++) {
    gene_index_data.insert(
        std::pair<int, std::string>(i, gene_expression_vector[i].gene_name));
  }
  return gene_index_data;
}

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

double get_dscore(std::vector<double> disease, std::vector<double> control) {
  int i;
  // combine vectors to do t-stat permutations
  std::vector<double> all_gene_data;
  all_gene_data.reserve(disease.size() + control.size()); // preallocate memory
  all_gene_data.insert(all_gene_data.end(), disease.begin(), disease.end());
  all_gene_data.insert(all_gene_data.end(), control.begin(), control.end());
  std::vector<double> permutation_t_stats;
  for (i = 0; i < 1000; i++) {
    // shuffle the order
    std::random_shuffle(all_gene_data.begin(), all_gene_data.end());
    // split the vector into 2
    std::vector<double> all_gene_data1(all_gene_data.begin(),
                                       all_gene_data.begin() + disease.size()),
        all_gene_data2(all_gene_data.begin() + disease.size(),
                       all_gene_data.end());
    // add the random t-stat to the t-stat list
    double random_t_stat = students_t_stat(all_gene_data1, all_gene_data2);
    permutation_t_stats.push_back(random_t_stat);
  }

  // find the d-score
  double t_stat = students_t_stat(disease, control);
  double random_t_stat_mean = mean(permutation_t_stats);
  double random_standard_deviation = standard_deviation(permutation_t_stats);
  return std::abs(t_stat - random_t_stat_mean) / random_standard_deviation;
}

gene_result process(gene_expression data_row) {
  return gene_result(data_row.gene_name,
                     get_dscore(data_row.renal_disease, data_row.control));
}
