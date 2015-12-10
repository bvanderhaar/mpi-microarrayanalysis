#include <iostream>
#include <string>
#include <vector>
#include <mpi.h>
#include "BVshared.h"
#include "BVgene.h"

#define MASTER 0
#define TAG 0
#define MAX 25
const int MSGSIZE = sizeof(double);

int main(int argc, char *argv[]) {
  int rows = 4550, column_size = 69, i;
  std::vector<std::vector<std::string>> vector =
      vectorize("NCI-60.csv", rows, column_size);
  std::vector<gene_expression> gene_expressions =
      gene_expression_vector(vector);

  int my_rank, source, num_nodes;
  char *message = new char[MSGSIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
  double program_start = MPI_Wtime();
  double d_score;
  if (my_rank != MASTER) {
    // pick row to process by rank
    d_score = get_dscore(gene_expressions[my_rank - 1].renal_disease,
                         gene_expressions[my_rank - 1].control);
    MPI_Send(&d_score, sizeof(double), MPI_DOUBLE, MASTER, TAG, MPI_COMM_WORLD);

  } else {
    MPI_Status status;
    std::vector<gene_result> gene_results;
    std::map<int, std::string> gene_name_index = gene_index(gene_expressions);
    for (source = 1; source < num_nodes; source++) {
      MPI_Recv(&d_score, sizeof(double), MPI_DOUBLE, source, TAG,
               MPI_COMM_WORLD, &status);
      std::string gene_name =
          gene_name_index.find(status.MPI_SOURCE - 1)->second;
      gene_results.push_back(gene_result(gene_name, d_score));
    }

    std::cout.precision(10);
    for (int i = 0; i < gene_results.size(); i++) {
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
