/*
 * =====================================================================================
 *
 *       Filename:  30_crivo_base.c
 *
 *    Description:  Crivo de Eratostenes, considerando pares e ímpares, com OPENMP
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
#include <omp.h>
#include <math.h>

//FALTA COLOCAR AS DIRETIVAS DO OPENMP
int eratosthenes(int lastNumber, int threads)
{
  
  omp_set_num_threads(threads);

  //PASSO 1
  char *isPrime = (char*)malloc((lastNumber+1)*sizeof(char));
  const int lastNumberSqrt = (int)sqrt((double)lastNumber);
  #pragma omp parallel for
    for (int i = 0; i <= lastNumber; i++) {
        isPrime[i] = 1;
    }
  
  //PASSO 2
  #pragma omp parallel for schedule(dynamic)
    for (int i = 2; i<= lastNumberSqrt; i++) {
        if (isPrime[i]) {
            for (int j = i*i; j <= lastNumber; j += i) {
                isPrime[j] = 0;
            }
        }
    }
  
  //PASSO 3
  int found = 0;
  #pragma omp parallel for reduction(+:found)
    for (int i = 2; i <=lastNumber; i++) {
        found += isPrime[i];
    }
  
  //FINALIZANDO
  free(isPrime);
  return found;
}

int main() {
    char *filename = "resultados.csv";
    FILE *fp = fopen(filename, "w");
    fprintf(fp,"%s;%s;%s;%s %s\n","N","threads","Tempo","Total","speedup");
    int threads = 2;
    int maximo = 100000000;
    int inicio = 10000000;
    int step = 10000000;
    int repeticoes = 10;
    double tempo_inicio,tempo_fim,tempo_sequencial=0,speedup=0,media_tempo = 0;
    /*
    ANÁLISE DE DESEMPENHO
    */
    for (int i=inicio;i<=maximo;i+=step) { //i -> limites
        for (int j=1;j<=threads;j++) { //j-> threads
            int total = 0;
            for (int k=1;k<=repeticoes;k++) {
                tempo_inicio = omp_get_wtime();
                total = eratosthenes(i,j);
                tempo_fim = omp_get_wtime();
                media_tempo = media_tempo + (tempo_fim-tempo_inicio);
            }
            media_tempo = media_tempo/(double)repeticoes;
            if (j==1) { //sequencial
                tempo_sequencial = media_tempo;
                speedup = 1;
            }
            else {
                speedup = tempo_sequencial/(media_tempo);
            }
            printf("%d %d %f %d %.2f\n",i,j,media_tempo,total,speedup);
            fprintf(fp,"%d;%d;%f;%d;%.2f\n",i,j,media_tempo,total,speedup);

        }
    }
    fclose(fp);
    return 0;
}