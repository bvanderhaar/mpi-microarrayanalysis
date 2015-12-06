#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

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
    std::cout << "Random T Stat (i, stat): " << i << ", " << random_t_stat
              << std::endl;
    permutation_t_stats.push_back(random_t_stat);
  }

  // find the d-score
  double t_stat = students_t_stat(data_row.renal_disease, data_row.control);
  double random_t_stat_mean = mean(permutation_t_stats);
  double random_standard_deviation = standard_deviation(permutation_t_stats);
  double d_score = std::abs((double)(t_stat - random_t_stat_mean)) /
                   random_standard_deviation;
  return gene_result(data_row.gene_name, d_score);
}
