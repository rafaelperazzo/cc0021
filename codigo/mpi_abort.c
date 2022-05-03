#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

float *gerar_vetor(int n);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    time_t t;
    srand(time(NULL)*rank);
    
    /*
    INICIO
    */

    if (rank==1) {
      
      
    }
    else {
      sleep(3);
      MPI_Abort(MPI_COMM_WORLD,0);
    }
    /*
    FIM
    */
    MPI_Finalize();
    
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}