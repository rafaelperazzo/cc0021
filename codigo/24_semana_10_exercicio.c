#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 100000000
#define SUBTAMANHO 50000000
#define max  10000

/*
1) Escrever função que dado um vetor, retorne a soma de seus valores
*/

long int soma_vetor(int *vetor, long int tamanho) {

    int i;
    long int soma = 0;
    for (i=0;i<tamanho;i++) {
        soma = soma + vetor[i];
    }
    return(soma);

}

int main(int argc, char** argv) {

    /*
    2) Iniciar as rotinas MPI
    */
    MPI_Init(NULL,NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    /*
    3) Iniciar variáveis “locais” de cada processo e as “globais” do rank 0. 
    */
    long int i;
    int *subvetor = NULL;
    int *vetor = NULL;
    double inicio_rand,fim_rand,tempo_rand,tempo_proc,inicio_proc,fim_proc,tempo_dist,fim_dist;
    /*
    4) Rank 0 gera o vetor aleatório
    */
    if (rank==0) {
        inicio_rand = MPI_Wtime();
        vetor = malloc(TAMANHO*sizeof(int));
        time_t t;
        srand((unsigned)time(&t));
        for (i=0;i<TAMANHO;i++) {
            int num = (rand() % (max+1));
            vetor[i] = num;
        }
        fim_rand = MPI_Wtime();
        tempo_rand = fim_rand-inicio_rand;
        printf("Tempo de geracao do vetor completo: %f\n",tempo_rand);
    }

    /*
    5) Rank 0 divide o vetor em 2 partes e distribui
    */
    if (rand==0) {
        inicio_proc = MPI_Wtime();
    }
    subvetor = malloc(SUBTAMANHO*sizeof(int));
    MPI_Scatter(vetor,SUBTAMANHO,MPI_INT,subvetor,SUBTAMANHO,MPI_INT,0,MPI_COMM_WORLD);
    if (rank==0) {
        tempo_dist = MPI_Wtime()-inicio_proc;
        printf("Tempo de distribuicao: %f\n",tempo_dist);
    }
    /*
    6) Cada processo calcula a soma do seu vetor individual
    */
    long int soma;
    soma = soma_vetor(subvetor,SUBTAMANHO);

    /*
    7) O processo 0 recebe os resultados
    */
    long int *resultados = NULL;
    if (rank==0) {
        resultados = malloc(nprocs*sizeof(long int));
    }
    MPI_Gather(&soma,1,MPI_LONG,resultados,1,MPI_LONG,0,MPI_COMM_WORLD);

    /*
    8) O processo 0 consolida e mostra o resultado final
    */

    if (rank==0) {
        long int soma_total=0;
        for (i=0; i<nprocs;i++) {
            soma_total = soma_total + resultados[i];
        }
        double media;
        media = soma_total/(double)TAMANHO;
        fim_proc = MPI_Wtime();
        tempo_proc = fim_proc-inicio_proc;
        printf("Tempo de processamento: %f\n",tempo_proc);
        printf("Proporcao da distribuicao em relacao ao processamento: %f\n", (tempo_dist/tempo_proc)*100);
        printf("Media: %f\n",media);
    }    

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}