#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000
#define TAMANHO 8

float *gerar_vetor(int n);
int menores_que(float x, float *vetor,int len);
void mostrar_vetor(int *vetor,int tamanho);
void mostrar_vetor_f(float *vetor,int tamanho);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    time_t t;
    
    int ELEMENTOS_POR_PROCESSO = (int)(TAMANHO/nprocs);
    /*
    INICIO
    */
    srand(time(NULL));
    int i,j;
    float *A = malloc(TAMANHO*sizeof(float));
    if (rank==0) {
        
        A = gerar_vetor(TAMANHO);
        MPI_Bcast(A,TAMANHO,MPI_FLOAT,0,MPI_COMM_WORLD);
    }
    else {
        MPI_Bcast(A,TAMANHO,MPI_FLOAT,0,MPI_COMM_WORLD);
    }
    
    
    int *B = malloc(ELEMENTOS_POR_PROCESSO*sizeof(int));
    int menores;
    int inicio,fim;
    inicio = rank*ELEMENTOS_POR_PROCESSO;
    fim = inicio+ELEMENTOS_POR_PROCESSO;
    
    int k = 0;
    for (i=inicio;i<fim;i++) {
        menores = menores_que(A[i],A,TAMANHO);
        B[k] = menores;
        k++;
    }
    
    int *todos = NULL;
    if (rank==0) {
        todos = malloc(TAMANHO*sizeof(int));
    }
    
    MPI_Gather(B,ELEMENTOS_POR_PROCESSO,MPI_INT,todos,ELEMENTOS_POR_PROCESSO,MPI_INT,0,MPI_COMM_WORLD);
    
    if (rank==0) {
        mostrar_vetor_f(A,TAMANHO);
        printf("\n*********************\n");
        mostrar_vetor(todos,TAMANHO);
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

int menores_que(float x, float *vetor,int len) {
    int i;
    int cont = 0;
    for (i=0;i<len;i++) {
        if (vetor[i]<x) {
            cont++;
        }
    }
    return (cont);
}

void mostrar_vetor(int *vetor,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]\n",vetor[i]);
    }
}

void mostrar_vetor_f(float *vetor,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]\n",vetor[i]);
    }
}