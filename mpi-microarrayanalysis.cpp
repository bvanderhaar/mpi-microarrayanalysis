#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>
#include "BVshared.h"
#include "BVgene.h"

#define MASTER 0
#define TAG 0
const int MESSAGE_SIZE = 50;

int main(int argc, char *argv[]) {
  int rows = 4550, column_size = 69, i, my_rank, num_nodes, source, start_row,
      end_row;
  double d_score, program_start = MPI_Wtime();
  std::string gene_name, message_str;
  char message[MESSAGE_SIZE];
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);
  std::vector<gene_expression> gene_expressions =
      gene_expression_vector(vector);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);

  if (my_rank != MASTER) {
    // pick rows to process by rank
    start_row = my_rank * 10;
    end_row = start_row - 10;
    for (i = start_row; i > end_row; i--) {
      d_score = get_dscore(gene_expressions[i].renal_disease,
                           gene_expressions[i].control);
      message_str = encode_gene_result(
          gene_result(gene_expressions[i].gene_name, d_score));
      MPI_Send((void *)message_str.c_str(), message_str.size(), MPI_CHAR,
               MASTER, i, MPI_COMM_WORLD);
    }
  } else {
    MPI_Status status;
    std::vector<gene_result> gene_results;
    std::map<int, std::string> gene_name_index = gene_index(gene_expressions);
    for (source = 1; source < rows; source++) {
      for (i = 0; i < 10; i++) {
        MPI_Recv(&message, MESSAGE_SIZE, MPI_DOUBLE, source, i, MPI_COMM_WORLD,
                 &status);
        std::string message_str(message);
        gene_results.push_back(decode_gene_result(message_str));
      }
    }
    std::cout.precision(10);
    for (i = 0; i < gene_results.size(); i++) {
      std::cout << gene_results[i].gene_name << ", " << gene_results[i].d_score
                << std::endl;
    }
    double program_end = MPI_Wtime();
    double program_elapsed = program_end - program_start;
    printf("Nodes, Message Size, Program Execution Time, %d,%lu,%f\n",
           num_nodes, sizeof(double), program_elapsed);
  }

  MPI_Finalize();

  return 0;
}
