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
  if (my_rank != MASTER) {
    // pick row to process by rank
    double d_score = get_dscore(gene_expressions[my_rank-1].renal_disease, gene_expressions[my_rank-1].control);
    MPI_Send(&d_score, sizeof(d_score), MPI_DOUBLE, MASTER, TAG,
             MPI_COMM_WORLD);

  } else {
    std::vector<gene_result> gene_results;
    ////printf("Num_nodes: %d\n", num_nodes);
    ////printf("Hello from Master (process %d)!\n", my_rank);
    MPI_Status status;
    for (source = 1; source < num_nodes; source++) {
      MPI_Recv(&d_score, MSGSIZE, MPI_DOUBLE, source, TAG, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      gene_results.push_back(gene_result())
    }

    double program_end = MPI_Wtime();
    double program_elapsed = program_end - program_start;
    printf("Nodes, Message Size, Program Execution Time, %d,%lld,%f\n",
           num_nodes, MSGSIZE, program_elapsed);
  }

  MPI_Finalize();

  return 0;
}
