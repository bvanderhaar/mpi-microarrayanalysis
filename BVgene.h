#include <string>
#include <map>
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

std::string encode_gene_result(gene_result);
gene_result decode_gene_result(std::string);
std::map<int, std::string>
gene_index(std::vector<gene_expression> gene_expression_vector);
std::vector<gene_expression>
gene_expression_vector(std::vector<std::vector<std::string>> raw_data);
double get_dscore(std::vector<double> disease, std::vector<double> control);
gene_result process(gene_expression gene_data);
