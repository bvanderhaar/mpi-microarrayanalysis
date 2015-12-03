#include <stdio.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>


string slurp(const string &filename) {
  ifstream in(filename, ifstream::in);
  stringstream sstr;
  sstr << in.rdbuf();
  string file = sstr.str();
  return file;
}



int main(int argc, char *argv[]) {
  stirng source_data = slurp("NCI-60.csv");

}
