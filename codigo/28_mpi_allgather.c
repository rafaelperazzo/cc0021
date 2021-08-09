#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 1000000
#define max  10000


int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    long int i;
    long int soma_total;
    int *vetor=NULL,*subvetor=NULL;
    long int quantidades;
    quantidades = 500000;

    if (rank==0) {
        printf("Total de elementos: %ld\n",quantidades);
        vetor = malloc(TAMANHO*sizeof(int));
        time_t t;
        srand((unsigned) time(&t));
        for (i=0;i<TAMANHO;i++) {
            int num = (rand() % (max+1));
            vetor[i] = num;
        }
    }
    subvetor = malloc(quantidades*sizeof(int));
    MPI_Scatter(vetor, quantidades, MPI_INT, subvetor,quantidades, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Calculando a soma do subvetor
    long int soma=0;
    for (i=0;i<quantidades;i++) {
        soma = soma + subvetor[i];
    }
    long int *somas = NULL;
    somas = malloc((nprocs)*sizeof(long int));
    MPI_Allgather(&soma, 1, MPI_LONG, somas, 1, MPI_LONG, MPI_COMM_WORLD);
    
    
    long int total=0;
    for (i=0;i<nprocs;i++) {
        total = total + somas[i];
        
    }
    printf("Total parcial[%d]:%ld\n",rank,somas[rank]);
    printf("Total: %ld\n",total);
    
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}