#include <string>
#include <vector>

struct gene_expression {
  std::string gene_name;
  std::vector<double> renal_disease;
  std::vector<double> control;
};

struct gene_result {
  std::string gene_name;
  double d_score;
  gene_result(std::string gene_name, double d_score)
      : gene_name(gene_name), d_score(d_score) {}
};

gene_result process(gene_expression gene_data);
