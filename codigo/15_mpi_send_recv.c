#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int nprocs;
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  int numero;
  if (rank == 0) {
      numero = -1;
      MPI_Send(&numero, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
      MPI_Recv(&numero, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Processo 1 recebeu o numero %d do processo 0\n", numero);
  }
  MPI_Finalize();
}