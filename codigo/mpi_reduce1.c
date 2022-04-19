#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENTOS_POR_PROCESSO 20

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

    //1) Cada processo começa gerando um vetor aleatório e calculando sua soma local
    float *vetor_local = gerar_vetor(ELEMENTOS_POR_PROCESSO);
    float soma_local = 0;
    for(int i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        soma_local = soma_local + vetor_local[i];
    }
    printf("Soma local do processo[%d]: %f\n",rank,soma_local);

    //2) Consolidação dos resultados (reduction)
    float soma_total;
    MPI_Reduce(&soma_local,&soma_total,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

    //3) Imprimindo o resultado consolidado (quem faz isso é o processo root)
    if(rank==0) {
        printf("Soma total: %f\n",soma_total);
    }
    free(vetor_local);
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