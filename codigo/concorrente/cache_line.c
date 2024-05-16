#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMANHO 512*1024*1024

int main() {

    int *vetor;
    vetor = (int *) malloc(TAMANHO*sizeof(int));
    double inicio,fim,tl1,tl2;
    //Primeiro loop
    inicio = omp_get_wtime();
    for (int i=0; i<TAMANHO; i+=64) {
        vetor[i] *= 3;
    }
    fim = omp_get_wtime();
    tl1 = fim-inicio;
    printf("Tempo loop 1: %.2f\n",tl1);

    return 0;
}