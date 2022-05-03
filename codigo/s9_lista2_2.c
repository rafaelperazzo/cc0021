/*
2) Desenvolva um programa paralelo que encontre o maior valor de um conjunto S com n 
numeros com p processadores.
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TOTAL 500000000

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

    double inicio,fim;
    if (rank==0) {
        inicio = MPI_Wtime();
    }
    int ELEMENTOS_POR_PROCESSO = (int)(TOTAL/nprocs);
    int i;
    float *subvetor = NULL;
    subvetor = gerar_vetor(ELEMENTOS_POR_PROCESSO);
    float maior_parcial = subvetor[0];
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        if (subvetor[i]>maior_parcial) {
            maior_parcial = subvetor[i];
        }
    }

    float maior_geral;
    MPI_Reduce(&maior_parcial,&maior_geral,1,MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);

    if (rank==0) {
        fim = MPI_Wtime();
        printf("Maior valor: %.5f\n",maior_geral);
        printf("Tempo: %.2f\n",fim-inicio);
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