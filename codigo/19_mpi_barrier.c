#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int numero;
    if (rank == 0) {
        printf("Processo master processando...\n");
        sleep(2);
    } 
    MPI_Barrier(MPI_COMM_WORLD);  
    if (rank!=0) {
        printf("Processo worker %d liberado\n",rank);
    }
    MPI_Finalize();
}