#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 10000
#define MAX  100

int gerar_numero_aleatorio(int max) {
    int num = (rand() % (max+1));
    return (num);
}

int *gerar_vetor_aleatorio(int tamanho) {
    int *vetor = malloc(tamanho*sizeof(int));
    for (int i=0;i<tamanho;i++) { 
        vetor[i] = gerar_numero_aleatorio(MAX);
    }
    return (vetor);
}

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
    
    time_t t;
    srand((unsigned) time(&t)*rank);
    /*
    Cada processo gera seu subvetor
    */
    int subtamanho = (int)(TAMANHO/nprocs);
    int *subvetor = NULL;
    subvetor = gerar_vetor_aleatorio(subtamanho);

    /*
    Cada processo calcula sua média
    */
    int soma = 0;
    for (int i=0;i<subtamanho;i++) {
        soma = soma + subvetor[i];
    }
    double media;
    media = soma/(double)(subtamanho);
    media = media/nprocs;

    /*
    Enviando cada média para todos os processos
    */
    double media_total;
    MPI_Allreduce(&media,&media_total,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
    
    /*
    Cada processo continua a calcular o somatório do desvio padrão
    */
    double soma_dp = 0;
    for (int i=0;i<subtamanho;i++) {
        soma_dp = soma_dp + (subvetor[i]-media_total)*(subvetor[i]-media_total);
    }

    /*
    Enviando resultados parciais para o processo root
    */

    double soma_total;
    MPI_Reduce(&soma_dp,&soma_total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    
    /*
    Consolidando os resultados e mostrando desvio padrão
    */
    if (rank==0) {
        double desvio_padrao;
        desvio_padrao = soma_total/(double)TAMANHO;
        desvio_padrao = sqrt(desvio_padrao);
        printf("Desvio padrao: %f\n",desvio_padrao);
    }

    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;

}