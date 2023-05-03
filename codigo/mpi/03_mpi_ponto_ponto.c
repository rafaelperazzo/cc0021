#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /*
    INICIO
    */
    int numero = 2;
    if (rank==0) {
        numero = -1;
        MPI_Send(&numero,1,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else if (rank==1) {
        MPI_Recv(&numero,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Processo [%d] recebeu valor %d\n",rank,numero);
    }
    else {
        printf("Processo [%d] não recebeu nada [%d]\n",rank,numero);
    }

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}