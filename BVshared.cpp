#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

double mean(std::vector<double> source) {
  double sum = 0, mean = 0;
  for (int i = 0; i < source.size(); i++) {
    sum += source[i];
  }
  mean = (double)sum / source.size();
  return mean;
}

double standard_deviation(std::vector<double> source) {
  int orig_mean = mean(source);
  std::vector<double> squared_source(source.size());
  for (int i = 0; i < source.size(); i++) {
    squared_source[i] = pow(source[i] - orig_mean, 2);
  }
  int squared_mean = mean(squared_source);
  return sqrt(squared_mean);
}

void print_1d_vector(std::vector<double> vector) {
  for (int i = 0; i < vector.size(); i++) {
    std::cout << vector[i] << ",";
  }
  std::cout << std::endl;
}
