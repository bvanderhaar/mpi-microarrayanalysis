#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

int main(int argc, char *argv[]) {
  int rows = 4550, column_size = 69, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);

  // "type" the matrix
  std::vector<gene_expression> gene_expressions =
      gene_expression_vector(vector);

  for (i = 0; i < rows; i++) {
    /*std::cout << "Processing renal: ";
    print_1d_vector(gene_expressions[i].renal_disease);
    std::cout << "Processing control: ";
    print_1d_vector(gene_expressions[i].control); */
    gene_result result = process(gene_expressions[i]);
    std::cout.precision(10);
    std::cout << "Gene name, D-score: " << result.gene_name << ", "
              << result.d_score << std::endl;
  }

  return 0;
}
