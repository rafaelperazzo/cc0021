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
      numero = 100;
      MPI_Bcast(&numero,1,MPI_INT,0,MPI_COMM_WORLD);
  } else {
      MPI_Bcast(&numero,1,MPI_INT,0,MPI_COMM_WORLD);
      printf("Processo %d recebeu o numero %d \n", rank,numero);
  }
  MPI_Finalize();
}