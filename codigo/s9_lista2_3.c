/*
3) Modifique o programa anterior para o problema de encontrar os dois maiores valores. 
Estime o speed up do algoritmo.
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TOTAL 500000000

float *gerar_vetor(int n);
void imprimir_vetor(float *vetor,int n);
float *max(float *vetor,int n);

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
    float maior_parcial2 = subvetor[0];
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        if (subvetor[i]>maior_parcial) {
            maior_parcial = subvetor[i];
        }
        if ((subvetor[i]>maior_parcial2)&&(subvetor[i]!=maior_parcial)) {
            maior_parcial2 = subvetor[i];
        }
    }
    float *maiores = malloc(2*sizeof(float));
    maiores[0] = maior_parcial;
    maiores[1] = maior_parcial2;
    //printf("Maiores de [%d]\n",rank);
    //imprimir_vetor(maiores,2);

    float *maiores_total = NULL;
    if (rank==0) {
        maiores_total = malloc(2*nprocs*sizeof(float));
    }
    
    MPI_Gather(maiores,2,MPI_FLOAT,maiores_total,2,MPI_FLOAT,0,MPI_COMM_WORLD);

    if (rank==0) {
        float *resultado = max(maiores_total,2*nprocs);
        fim = MPI_Wtime();
        printf("Maior valor: %.10f\n",resultado[0]);
        printf("Segundo maior valor: %.10f\n",resultado[1]);
        printf("Tempo: %.10f\n",fim-inicio);
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

void imprimir_vetor(float *vetor,int n) {

    int i;
    for (i=0;i<n;i++) {
        printf("[%.10f]\n",vetor[i]);
    }

}

float *max(float *vetor,int n) {
    int i;
    float maior = vetor[0];
    float maior2 = vetor[0];
    float *resultado = malloc(2*sizeof(float));
    for (i=0;i<n;i++) {
        if (vetor[i]>maior) {
            maior = vetor[i];
        }
        if ((vetor[i]>maior2)&&(vetor[i]!=maior)) {
            maior2 = vetor[i];
        }
    }
    resultado[0] = maior;
    resultado[1] = maior2;
    return (resultado);
}