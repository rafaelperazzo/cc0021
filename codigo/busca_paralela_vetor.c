#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 90000000
#define max  90000000

int main () {
    //INICIANDO GERADOR DE NÚMERO ALEATÓRIO
    time_t t;
    srand((unsigned) time(&t));
    //INICIANDO VETOR
    int n  = 109382;
    long int *vetor;
    vetor = malloc(TAMANHO*sizeof(long int));
    int i;
    for (i=0;i<TAMANHO;i++) {
        int num = (rand() % (max+1));
        vetor[i] = num;
    }
    double inicio = omp_get_wtime();
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
			for (i=0;i<TAMANHO;i++) {
                if (vetor[i]==n) {
                    printf("Thread[%d] ACHOU: %ld\n", omp_get_thread_num(),vetor[i]);
                }
			}
	}
	double fim = omp_get_wtime();
	printf("%f\n",fim-inicio);
}

