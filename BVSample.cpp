#include <iostream>
#include <string>
#include <vector>
#include "BVshared.h"
#include "BVgene.h"

int main(int argc, char *argv[]) {
  static const double gene1_disease_array[] = {0.1,0.2,0.3};
  static const double gene1_control_array[] = {2.3,3.1,2.5};
  std::vector<double> gene1_disease (gene1_disease_array, gene1_disease_array + sizeof(gene1_disease_array) / sizeof(gene1_disease_array[0]));
  std::vector<double> gene1_control (gene1_control_array, gene1_control_array + sizeof(gene1_control_array) / sizeof(gene1_control_array[0]));
  std::cout << "gene1_disease mean: " << mean(gene1_disease) << std::endl;
  std::cout << "gene1_control mean: " << mean(gene1_control) << std::endl;
  std::cout << "gene1_disease standard deviation: " << standard_deviation(gene1_disease) << std::endl;
  std::cout << "gene1_control standard deviation: " << standard_deviation(gene1_control) << std::endl;
  std::cout << "Gene1 T-Stat: " << students_t_stat(gene1_disease, gene1_control) << std::endl;
}
