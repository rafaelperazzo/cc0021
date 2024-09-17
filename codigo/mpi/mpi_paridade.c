#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 10000000
#define MAX 1

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

    int *vetor_local = malloc(TAMANHO/nprocs*sizeof(int));
    MPI_Scatter(vetor, TAMANHO/nprocs, MPI_INT, vetor_local, TAMANHO/nprocs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank==0) {
        inicio = MPI_Wtime();
    }

    /**
     * Cada processo calcula a quantidade de 1's do vetor local.
     * 
    */

    int qtd_local = 0;
    for (int i=0;i<TAMANHO/nprocs;i++) {
        if (vetor_local[i] == 1) {
            qtd_local++;
        }
    }
    /**
     * O processo rank #0 recebe as quantidades locais e calcula a quantidade total.
     * 
     */
    int *qtds_locais = NULL;
    if (rank==0) {
        qtds_locais = malloc(nprocs*sizeof(int));
    }
    MPI_Gather(&qtd_local, 1, MPI_INT, qtds_locais, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int qtd_total = 0;
    if (rank==0) {
        for (int i=0;i<nprocs;i++) {
            qtd_total += qtds_locais[i];
        }
        printf("Quantidade de 1's: %d\n", qtd_total);
        if (qtd_total%2==0) {
            printf("Paridade: Par\n");
        } else {
            printf("Paridade: Ímpar. Acrescentar um zero.\n");
        }
        printf("Tempo de execução: %f\n", MPI_Wtime()-inicio);
    }

    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;

}