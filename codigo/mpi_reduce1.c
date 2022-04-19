#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define ELEMENTOS_POR_PROCESSO 20

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
    
    //1) Cada processo começa gerando um vetor aleatório e calculando sua soma local
    int *vetor_local = gerar_vetor(ELEMENTOS_POR_PROCESSO);
    int soma_local = 0;
    for(int i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        soma_local = soma_local + vetor_local[i];
    }
    printf("Soma local do processo[%d]: %d\n",rank,soma_local);

    //2) Consolidação dos resultados (reduction)
    int soma_total;
    MPI_Reduce(&soma_local,&soma_total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    //3) Imprimindo o resultado consolidado (quem faz isso é o processo root)
    if(rank==0) {
        printf("Soma total: %d\n",soma_total);
    }
    free(vetor_local);
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