#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int *gerar_vetor(int n);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    time_t t;
    srand((unsigned) time(&t));
    /*
    INICIO
    */


    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

int *gerar_vetor(int n) {
    int *vetor;
    int i;
    vetor = malloc(n*sizeof(int));
    for (i=0;i<n;i++) {
        int num = (rand() % (MAX+1));
        vetor[i] = num;
    }
    return vetor;
}