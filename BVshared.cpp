#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void print_1d_vector(std::vector<double> vector) {
  for (int i = 0; i < vector.size(); i++) {
    std::cout << vector[i] << ",";
  }
  std::cout << std::endl;
}

bool vector_has_inf(std::vector<double> source) {
  for (int i = 0; i < source.size(); i++) {
    if (std::isnan(source[i]) || std::isinf(source[i])) {
      return true;
    }
  }
  return false;
}

std::string slurp(const std::string &filename) {
  std::ifstream in(filename, std::ifstream::in);
  std::stringstream sstr;
  sstr << in.rdbuf();
  std::string file = sstr.str();
  return file;
}

std::vector<std::vector<std::string>> vectorize(std::string filename, int rows,
                                                int column_size) {
  int current_row, current_col;
  std::string current_line, current_pos;
  std::vector<std::vector<std::string>> data(
      rows, std::vector<std::string>(column_size, ""));
  std::string source_data = slurp(filename);
  std::istringstream source_data_stream(source_data);
  for (current_row = 0; std::getline(source_data_stream, current_line);
       current_row++) {
    std::stringstream row_stream(current_line);
    for (current_col = 0; std::getline(row_stream, current_pos, ',');
         current_col++) {
      data[current_row][current_col] = current_pos;
    }
  }
  return data;
}

double vector_sum(std::vector<double> source) {
  double sum = 0;
  for (int i = 0; i < source.size(); i++) {
    sum = sum + source[i];
  }
  return sum;
}

double mean(std::vector<double> source) {
  return vector_sum(source) / source.size();
}

double standard_deviation(std::vector<double> source) {
  double source_mean = mean(source);
  std::vector<double> squared_source;
  for (int i = 0; i < source.size(); i++) {
    squared_source.push_back(pow((source[i] - source_mean), 2));
  }
  double variance = vector_sum(squared_source) / (source.size() - 1);
  return sqrt(variance);
}

double students_t_stat(std::vector<double> source1,
                       std::vector<double> source2) {
  double mean_diff = mean(source1) - mean(source2);
  double source1_avg_std_dev =
      pow(standard_deviation(source1), 2) / source1.size();
  double source2_avg_std_dev =
      pow(standard_deviation(source2), 2) / source2.size();
  return mean_diff / (sqrt(source1_avg_std_dev + source2_avg_std_dev));
}
