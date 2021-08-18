/*
 * =====================================================================================
 *
 *       Filename:  30_crivo_base.c
 *
 *    Description:  Crivo de Eratostenes, considerando pares e ímpares, com Open MPI
 *
 *        Version:  1.0
 *        Created:  17/08/2021 10:19
 *       Revision:  none
 *       Compiler:  gcc/g++
 *
 *         Author:  Rafael Perazzo B Mota
 *          email:  rafael.mota@ufca.edu.br
 *   Organization:  UNIVERSIDADE FEDERAL DO CARIRI
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

void eratostenes_mpi(int lastNumber,int ELEMENTOS_POR_PROCESSO,int rank, int nprocs,FILE *fp) {
    /*
    *************************
    PASSO 1: Cada processo gera seu subvetor
    *************************
    */
    double tempo_inicio,tempo_fim,tempo_sequencial=0,speedup=0,media_tempo = 0;
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0) {
        tempo_inicio = MPI_Wtime();
    }
    char *isPrime = (char*)malloc((ELEMENTOS_POR_PROCESSO)*sizeof(char));
    const int lastNumberSqrt = (int)sqrt((double)lastNumber);

    for (int i = 0; i < ELEMENTOS_POR_PROCESSO; i++) {
        isPrime[i] = 1;
    }

    /*
    *************************
    PASSO 2: Cada processo marca os números não primos com o valor 0
    *************************
    */
    int index;
    if (rank == 0)
		index = 2;
    
    int primo = 2;
    int primeiro,limite_inferior;
    limite_inferior = rank*ELEMENTOS_POR_PROCESSO;
    
    do {
        if (primo * primo > limite_inferior)
		{
			primeiro = primo * primo - limite_inferior;
		}
		else 
		{
			if (!(limite_inferior % primo))
				primeiro = 0;
			else {
				primeiro = primo - (limite_inferior % primo);
            }
		}
        
        for (int i = primeiro; i < ELEMENTOS_POR_PROCESSO; i += primo) {
			isPrime[i] = 0;
        }
		
        if (rank == 0) /* parent process */
		{
            while (isPrime[++index]==0);
            primo = index;
		}
        MPI_Bcast(&primo, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
    } while (primo*primo<=lastNumber);

    /*
    *************************
    PASSO 3: Cada processo conta os números não marcados
    *************************
    */
    int found = 0;
    int global_primos;
    for (int i = 0; i <ELEMENTOS_POR_PROCESSO; i++) {
        found += isPrime[i];
    }
    
    /*
    *************************
    FINAL DO PASSO 3: Redução para consolidação das somas
    *************************
    */
    MPI_Reduce(&found, &global_primos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0) {
        tempo_fim = MPI_Wtime();
    }
    if (rank==0) {
        printf("Total de primos: %d\n",global_primos-2);
        printf("Tempo: %f\n",tempo_fim-tempo_inicio);
        fprintf(fp,"%d;%d;%.4f;%d\n",lastNumber,nprocs,tempo_fim-tempo_inicio,global_primos-2);
    }   
    free(isPrime);
}

int main() {
    
    int lastNumber = 1000000000;
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    int ELEMENTOS_POR_PROCESSO = (int)(lastNumber/nprocs);
    if (lastNumber%ELEMENTOS_POR_PROCESSO!=0) {
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    
    FILE *fp=NULL; 
    
    if (rank==0) {
        char *filename = "resultados_mpi.csv";
        fp = fopen(filename, "a");
        //fprintf(fp,"%s;%s;%s;%s\n","N","threads","Tempo","Total");
    }
    
    eratostenes_mpi(lastNumber,ELEMENTOS_POR_PROCESSO,rank,nprocs,fp);
    
    if (rank==0) {
        fclose(fp);
    }
    
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}