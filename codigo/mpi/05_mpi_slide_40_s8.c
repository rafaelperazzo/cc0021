#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 1000

float *gerar_vetor(int n);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    time_t t;
    srand(time(NULL));
    
    /*
    INICIO
    */

    if (rank==0) { 
        //GERAR VETOR ALEATÓRIO E ENVIAR POR BROADCAST PARA OS PROCESSOS 1 E 2
        float *vetor;
        vetor = gerar_vetor(TAMANHO);
        float soma = 0;
        float soma_dobro = 0;
        //ENVIAR PARA OS DEMAIS PROCESSOS
        MPI_Bcast(vetor,TAMANHO,MPI_FLOAT,0,MPI_COMM_WORLD);
        //RECEBE A SOMA DO PROCESSO 1
        MPI_Recv(&soma,1,MPI_FLOAT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //RECEBE A SOMA DO DOBRO DO PROCESSO 2
        MPI_Recv(&soma_dobro,1,MPI_FLOAT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //MOSTRANDO OS 2 RESULTADOS NA TELA
        printf("Soma: %.10f\n",soma);
        printf("Soma dobro: %.10f\n",soma_dobro);
    }
    else {
        float *vetor;
        int i;
        float soma = 0;
        vetor = (float *)malloc(sizeof(float) * TAMANHO);
        //RECEBER VETOR DO PROCESSO ROOT
        MPI_Bcast(vetor,TAMANHO,MPI_FLOAT,0,MPI_COMM_WORLD);
        if (rank==1) {
            //CALCULAR O SOMATÓRIO DOS ELEMENTOS
            for (i=0;i<=TAMANHO;i++) {
                soma = soma + vetor[i];
            }
            //ENVIAR RESULTADO AO PROCESSO ROOT
            MPI_Send(&soma,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);
        }
        if (rank==2) {
            //CALCULAR O SOMATÓRIO DO DOBRO DOS ELEMENTOS
            for (i=0;i<=TAMANHO;i++) {
                soma = soma + (2*vetor[i]);
            }
            //ENVIAR RESULTADO AO PROCESSO ROOT
            MPI_Send(&soma,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);
        }
    }

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float) RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}