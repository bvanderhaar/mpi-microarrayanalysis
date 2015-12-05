#include <stdio.h>
#include <string>
#include <unistd.h>
#include <mpi.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "BVshared.h"

#define MASTER 0
#define TAG 0
#define MAX 25
const long long MSGSIZE = 99999;

int main(int argc, char *argv[]) {
  // stirng source_data = slurp("NCI-60.csv");

  int my_rank, source, num_nodes;
  char *message = new char[MSGSIZE];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
  double program_start = MPI_Wtime();
  if (my_rank != MASTER) {
    double message_sent = MPI_Wtime();
    for (long long i = 0; i < MSGSIZE; i++) {
      message[i] = 'a' + (std::rand() % 26);
    }
    MPI_Send(&message, strlen(message) + 1, MPI_CHAR, MASTER, TAG,
             MPI_COMM_WORLD);

  } else {
    printf("Num_nodes: %d\n", num_nodes);
    printf("Hello from Master (process %d)!\n", my_rank);
    MPI_Status status;
    for (source = 1; source < num_nodes; source++) {
      MPI_Recv(&message, MSGSIZE, MPI_CHAR, source, TAG, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
    }

    double program_end = MPI_Wtime();
    double program_elapsed = program_end - program_start;
    printf("Nodes, Message Size, Program Execution Time, %d,%lld,%f\n",
           num_nodes, MSGSIZE, program_elapsed);
  }

  MPI_Finalize();

  return 0;
}
