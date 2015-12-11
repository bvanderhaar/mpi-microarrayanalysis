#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

int main(int argc, char *argv[]) {
  int rows = 4550, column_size = 69, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);

  std::vector<gene_expression> gene_expressions =
      gene_expression_vector(vector);
  std::map<int, std::string> gene_name_index = gene_index(gene_expressions);

  // indicate output format
  std::cout << "Gene name, D-Score" << std::endl;
  clock_t cpu_start = clock();
  for (i = 0; i < gene_expressions.size(); i++) {
    gene_result result = process(gene_expressions[i]);
    std::cout.precision(10);
    std::cout << result.gene_name << ", " << result.d_score << std::endl;
  }
  clock_t cpu_stop = clock();
  double elapsed_cpu = double(cpu_stop - cpu_start) / (CLOCKS_PER_SEC / 1000);
  std::cout << "CPU Time Taken (msec): " << elapsed_cpu << std::endl;
  return 0;
}
