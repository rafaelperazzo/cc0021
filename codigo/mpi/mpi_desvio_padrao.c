#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 10000000
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

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_float(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.2f]",v[i]);
    }
    printf("\n");
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
    srand(time(NULL));
    double inicio;
    /**
    * O processo rank #0 gera o vetor inteiro;
    */
    int *vetor = NULL;
    if (rank == 0) {
        vetor = gerar_vetor_aleatorio(TAMANHO);
        //mostrar_vetor_inteiro(vetor, TAMANHO);
    }
    /**
     * O processo rank #0 divide o vetor em partes iguais e distribui para os demais processos.
     * 
     */

    if (rank==0) {
        inicio = MPI_Wtime();
    }

    int *vetor_local = malloc(TAMANHO/nprocs*sizeof(int));
    MPI_Scatter(vetor, TAMANHO/nprocs, MPI_INT, vetor_local, TAMANHO/nprocs, MPI_INT, 0, MPI_COMM_WORLD);

    /**
     * Cada processo calcula a soma dos elementos do vetor local.
     */
    float soma_local = 0;

    for (int i=0;i<TAMANHO/nprocs;i++) {
        soma_local += vetor_local[i];
    }
    /**
     * O processo rank #0 recebe as somas locais e calcula a soma total.
     * 
     */
    float *somas_locais = NULL;
    if (rank==0) {
        somas_locais = malloc(nprocs*sizeof(float));
    }

    MPI_Gather(&soma_local, 1, MPI_FLOAT, somas_locais, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    float soma_total = 0;
    float media;
    if (rank==0) {
        for (int i=0;i<nprocs;i++) {
            soma_total += somas_locais[i];
        }
        media = soma_total/(float)TAMANHO;
        printf("Média: %f\n", media);
    }

    MPI_Bcast(&media, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    /**
     * Cada processo calcula a soma dos quadrados da diferença entre o elemento e a média.
     */
    float soma_quadrados_local = 0;
    for (int i=0;i<TAMANHO/nprocs;i++) {
        soma_quadrados_local += (vetor_local[i]-media)*(vetor_local[i]-media);
    }

    /**
     * O processo rank #0 recebe as somas dos quadrados locais e calcula a soma total.
     */
    float *somas_quadrados_locais = NULL;
    if (rank==0) {
        somas_quadrados_locais = malloc(nprocs*sizeof(float));
    }
    MPI_Gather(&soma_quadrados_local, 1, MPI_FLOAT, somas_quadrados_locais, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    float soma_quadrados_total = 0;
    if (rank==0) {
        //mostrar_vetor_float(somas_quadrados_locais, nprocs);
        for (int i=0;i<nprocs;i++) {
            soma_quadrados_total += somas_quadrados_locais[i];
        }
        float dp = sqrt(soma_quadrados_total/(float)TAMANHO);
        printf("Desvio padrão: %f\n", dp);
        printf("Tempo de execução: %f\n", MPI_Wtime()-inicio);
    }

    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;

}