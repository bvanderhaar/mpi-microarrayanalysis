#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>
#include "BVshared.h"
#include "BVgene.h"

#define MASTER 0
#define TAG 0
const int MESSAGE_SIZE = 500;

int main(int argc, char *argv[]) {
  int rows = 4550, column_size = 69, i, my_rank, num_nodes, source, start_row,
      end_row, number_amount;
  double program_start = MPI_Wtime(), result;
  double buffered_messages[rows];
  MPI_Request requests[rows];
  std::string gene_name, message_str;
  double message;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);
  std::vector<gene_expression> gene_expressions =
      gene_expression_vector(vector);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);

  if (my_rank != MASTER) {
    // pick rows to process by rank
    //std::cout << my_rank << " rank started processing" << std::endl;
    end_row = my_rank * 10;
    if (end_row < rows) {
      start_row = end_row - 10;
      for (i = start_row; i < end_row; i++) {
        std::cout << i << " row processing" << std::endl;
        double message = get_dscore(gene_expressions[i].renal_disease,
                                    gene_expressions[i].control);
        MPI_Send(&message, sizeof(double), MPI_DOUBLE, MASTER, i,
                 MPI_COMM_WORLD);
      }
    }
  } else {
    std::vector<gene_result> gene_results;
    // std::map<int, std::string> gene_name_index =
    // gene_index(gene_expressions);
    for (i = 0; i < rows; i++) {
      //std::cout << i << " row waiting for processing" << std::endl;
      MPI_Irecv(&buffered_messages[i], sizeof(double), MPI_DOUBLE,
                MPI_ANY_SOURCE, i, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(rows - 1, requests, MPI_STATUSES_IGNORE);
    std::map<int, std::string> gene_name_index = gene_index(gene_expressions);
    for (i = 0; i < rows; i++) {
      std::string gene_name = gene_name_index.find(i)->second;
      gene_results.push_back(gene_result(gene_name, buffered_messages[i]));
    }

    double program_end = MPI_Wtime();
    double program_elapsed = program_end - program_start;

    std::cout.precision(10);
    for (i = 0; i < gene_results.size(); i++) {
      std::cout << gene_results[i].gene_name << ", " << gene_results[i].d_score
                << std::endl;
    }

    printf("Nodes, Message Size, Program Execution Time, %d,%lu,%f\n",
           num_nodes, sizeof(double), program_elapsed);
  }

  MPI_Finalize();

  return 0;
}
