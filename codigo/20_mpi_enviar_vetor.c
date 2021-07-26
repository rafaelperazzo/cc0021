#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 1000
#define max  10000


int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (nprocs>3) {
        MPI_Abort(MPI_COMM_WORLD,1);
        MPI_Finalize();
    }
    long int i;
    
    if (rank==0) {
        /*
        Gerar o vetor, distribuir carga para os demais processos
        */
        //Gerando o vetor
        long int soma_total,soma_total_dobro;
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        time_t t;
        srand((unsigned) time(&t));
        for (i=0;i<TAMANHO;i++) {
            long int num = (rand() % (max+1));
            vetor[i] = num;
        }
        MPI_Bcast(vetor,TAMANHO,MPI_LONG,0,MPI_COMM_WORLD);
        MPI_Recv(&soma_total, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&soma_total_dobro, 1, MPI_LONG, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Total: %ld\n",soma_total);
        printf("Total: %ld\n",soma_total_dobro);
    }
    else if (rank==1) {
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        MPI_Bcast(vetor,TAMANHO,MPI_LONG,0,MPI_COMM_WORLD);
        //Somar
        long int soma=0;
        for (i=0; i<TAMANHO;i++) {
            soma = soma + vetor[i];
        }
        MPI_Send(&soma, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }
    else if (rank==2) {
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        MPI_Bcast(vetor,TAMANHO,MPI_LONG,0,MPI_COMM_WORLD);
        //Soma do dobro
        long int soma = 0;
        for (i=0; i<TAMANHO;i++) {
            soma = soma + 2*vetor[i];
        }
        MPI_Send(&soma, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }

    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Finalize();
    return 0;
}