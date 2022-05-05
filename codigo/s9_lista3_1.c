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
    float *a = NULL;
    a = gerar_vetor(ELEMENTOS_POR_PROCESSO);
    float *b = NULL;
    b = gerar_vetor(ELEMENTOS_POR_PROCESSO);
    float produto_parcial = 0;
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        produto_parcial = produto_parcial + a[i]*b[i];
    }

    float produto_total;
    MPI_Reduce(&produto_parcial,&produto_total,1,MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);

    if (rank==0) {
        fim = MPI_Wtime();
        printf("Quantidade de processos: %d\n",nprocs);
        printf("Produto escalar: %.5f\n",produto_total);
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