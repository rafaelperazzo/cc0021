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
    VARIÁVEIS GLOBAIS
    */
    long int quantidades = (long int)(TAMANHO/nprocs); //Quantidade de elementos de cada subvetor
    long int i; //Utilizada no laço
    long int soma; //Soma de cada subvetor
    double inicio,fim; //Para medição do tempo
    
    /*
    Processo gerando o vetor aleatório
    */
    inicio = MPI_Wtime();
    time_t t;
    srand((unsigned) time(&t));
    long int *vetor;
    vetor = malloc(quantidades*sizeof(long int));
    for (i=0;i<quantidades;i++) {
        long int num = (rand() % (max+1));
        vetor[i] = num;
    }
    
    soma = 0;
    /*
    Calculando o somatório do vetor local
    */
    for (i=0;i<quantidades;i++) {
        soma = soma + vetor[i];
    }
    
    /*
    CONSOLIDANDO RESULTADOS: Somando cada soma local na soma_geral
    */
    long int soma_geral;
    MPI_Reduce(&soma, &soma_geral, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0) {
        fim = MPI_Wtime();
        printf("Soma total: %ld\n",soma_geral); //Mostrando a soma consolidada
        printf("Media: %.5f\n",soma_geral/(double)TAMANHO); //Calculando a média
        printf("Tempo de processamento: %f\n",fim-inicio); //Mostrando tempo de processamento geral, até a consolidação
    }
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Finalize();
    return 0;
}