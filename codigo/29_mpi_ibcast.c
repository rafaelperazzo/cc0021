#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <unistd.h>

int main(int argc, char **argv)
{
  int message = 1;
  int  i, rank, size;
  MPI_Status status;
  MPI_Request request; 
  int root = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == root)
  {
    message = 555;
    MPI_Ibcast(&message, 1, MPI_INT, root, MPI_COMM_WORLD,&request);
    MPI_Wait (&request, &status);
  }
  else {
    usleep(5000000);
    MPI_Ibcast(&message, 1, MPI_INT, root, MPI_COMM_WORLD,&request);
    //MPI_Wait (&request, &status);
    printf( "Message: %d\n", message);
  }
  
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
}