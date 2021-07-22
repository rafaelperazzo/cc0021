#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 1000000000
#define max  100000


int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (nprocs>2) {
        MPI_Abort(MPI_COMM_WORLD,1);
        MPI_Finalize();
    }
    /*
    AQUI VEM A ORGANIZAÇÃO DA SOLUÇÃO PARALELA - INÍCIO DO MPI
    */
    long int quantidades = (long int)(TAMANHO/nprocs);
    long int i;
    long int soma;
    double inicio,fim;
    if (rank==0) {
        /*
        Processo Mestre gerando o vetor aleatório
        */
        inicio = MPI_Wtime();
        time_t t;
        srand((unsigned) time(&t));
        long int *vetor;
        vetor = malloc(TAMANHO*sizeof(long int));
        for (i=0;i<TAMANHO;i++) {
            long int num = (rand() % (max+1));
            vetor[i] = num;
        }
        fim = MPI_Wtime();
        printf("Tempo para gerar vetor: %f\n",fim-inicio);
        /*
        Processo mestre fazendo distribuição do vetor para um segundo processo
        */
        if (nprocs==2) {
            inicio = MPI_Wtime();
            long int *sub_vetor;
            sub_vetor = &vetor[0+quantidades];
            MPI_Send( sub_vetor , quantidades , MPI_LONG , 1 , 0 , MPI_COMM_WORLD);
            fim = MPI_Wtime();
            printf("Tempo para distribuir vetor: %f\n",fim-inicio);
        } 
        
        /*
        PROCESSO MESTRE CALCULANDO SOMA DA PRIMEIRA METADE DO VETOR
        */
        printf("----------> INICIANDO PROCESSAMENTO <-----------\n");
        inicio = MPI_Wtime();
        for (i=0;i<quantidades;i++) {
            soma = soma + vetor[i];
        }
    }
    else {
        /*
        PROCESSO 1 RECEBENDO DADOS DA SEGUNDA METADE DO VETOR
        */
        long int *sub_vetor;
        sub_vetor =  malloc(quantidades*sizeof(long int));
        MPI_Recv( sub_vetor , quantidades , MPI_LONG , 0 , 0 , MPI_COMM_WORLD , &status);
        /*
        PROCESSO 1 CALCULANDO A SOMA DA SEGUNDA METADE DO VETOR
        */
        for (i=0;i<quantidades;i++) {
            soma = soma + sub_vetor[i];
        }
    }
    /*
    CONSOLIDANDO RESULTADOS
    */
    long int soma_geral;
    MPI_Reduce(&soma, &soma_geral, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0) {
        fim = MPI_Wtime();
        printf("Soma total: %ld\n",soma_geral);
        printf("Media: %.5f\n",soma_geral/(double)TAMANHO);
        printf("Tempo de processamento: %f\n",fim-inicio);
    }
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Finalize();
    return 0;
}