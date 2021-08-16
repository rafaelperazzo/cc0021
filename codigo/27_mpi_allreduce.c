#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 1000
#define ELEMENTOS_POR_PROCESSO 500
#define max  10000

int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    /*
    Cada processo gera seu subvetor
    */
    long int *vetor;
    long int i;
    vetor = malloc(ELEMENTOS_POR_PROCESSO*sizeof(long int));
    time_t t;
    srand((unsigned) time(&t));
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        long int num = (rand() % (max+1));
        vetor[i] = num;
    }

    /*
    Calculando a soma local
    */
   long int soma_local = 0;
    for (i=0;i<ELEMENTOS_POR_PROCESSO;i++) {
        soma_local = soma_local + vetor[i];
    }

    long int soma_total;
    MPI_Allreduce(&soma_local,&soma_total,1,MPI_LONG,MPI_SUM,MPI_COMM_WORLD);

    /*
    Todos os processos recebem a soma global
    */
    printf("[PROCESSO %d - %s] recebeu a soma total %ld\n",rank,processor_name,soma_total);
    
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}