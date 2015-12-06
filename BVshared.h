
std::string slurp(const std::string &filename);
std::vector<std::vector<std::string>> vectorize(std::string filename, int rows,
                                                int column_size);
double mean(std::vector<double> source);
double standard_deviation(std::vector<double> source);
void print_1d_vector(std::vector<double> vector);
double students_t_stat(std::vector<double> source1,
                       std::vector<double> source2);
