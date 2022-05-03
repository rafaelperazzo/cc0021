/*
1) Desenvolva um programa paralelo (com p processadores) para verificar a paridade de um 
arquivo binário (considere um vetor binário). 
Ou seja, verifique o numero de 0’s e 1’s existentes no arquivo e 
adicione um 0 ou um 1 ao arquivo de tal forma que o número de 1’s seja par.

*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TOTAL 500000000

float *gerar_vetor(int n);
int *gerar_vetor_binario(int n);

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
    int *subvetor = NULL;
    subvetor = gerar_vetor_binario(ELEMENTOS_POR_PROCESSO);
    int cont_parcial = 0;
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        if (subvetor[i]==1) {
            cont_parcial = cont_parcial + 1;
        }
    }
    int cont_total;
    MPI_Reduce( &cont_parcial , &cont_total , 1 , MPI_INT , MPI_SUM , 0 , MPI_COMM_WORLD);

    if (rank==0) {
        fim = MPI_Wtime();
        if (cont_total%2==0) {
            printf("Adicionando um 0 ao arquivo(%d)...\n",cont_total);
        }
        else {
            printf("Adicionando um 1 ao arquivo(%d)...\n",cont_total);
        }
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

int *gerar_vetor_binario(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = rand() % 2;
        vetor[i] = num;
    }
    return vetor;
}