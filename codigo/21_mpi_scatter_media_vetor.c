#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 9
#define max  10


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
    long int *vetor=NULL,*subvetor=NULL;
    long int quantidades;
    quantidades = (long int)(TAMANHO/(int)(nprocs));

    if (rank==0) {
        printf("Total de elementos: %ld\n",quantidades);
        vetor = malloc(TAMANHO*sizeof(long int));
        time_t t;
        srand((unsigned) time(&t));
        for (i=0;i<TAMANHO;i++) {
            long int num = (rand() % (max+1));
            vetor[i] = num;
        }
        
    }
    subvetor = malloc(quantidades*sizeof(long int));
    MPI_Scatter(vetor, quantidades, MPI_LONG, subvetor,quantidades, MPI_LONG, 0, MPI_COMM_WORLD);
    
    //Calculando a soma do subvetor
    long int soma;
    
    for (i=0;i<quantidades;i++) {
        soma = soma + subvetor[i];
    }
    long int *somas = NULL;
    if (rank==0) {
        for (i=0;i<TAMANHO;i++) {
            printf("%ld\n",vetor[i]);
        }
        somas = malloc((nprocs)*sizeof(long int));
    }
    MPI_Gather(&soma, 1, MPI_LONG, somas, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    
    if (rank==0) {
        long int total=0;
        for (i=1;i<nprocs;i++) {
            total = total + somas[i];
            printf("TOtal parcial[%ld]:%ld\n",i,somas[i]);
        }
        printf("Total: %ld\n",total);
        total = 0;
        for (i=0;i<TAMANHO;i++) {
            total = total + vetor[i];
        }
        printf("Total: %ld\n",total);
    }
    
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}