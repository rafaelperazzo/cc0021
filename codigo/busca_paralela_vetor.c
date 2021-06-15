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

    double inicio,fim;
    //EXECUÇÃO SERIAL
    inicio = omp_get_wtime();
    for (i=0;i<TAMANHO;i++) {
        if (vetor[i]==n) {
            printf("Thread[%d] ACHOU: %ld\n", omp_get_thread_num(),vetor[i]);
        }
    }
    fim = omp_get_wtime();
    double t_serial = fim-inicio;
    printf("Execucao serial: %f\n",t_serial);
    //EXECUÇÃO PARALELA
    inicio = omp_get_wtime();
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
			for (i=0;i<TAMANHO;i++) {
                if (vetor[i]==n) {
                    printf("Thread[%d] ACHOU: %ld\n", omp_get_thread_num(),vetor[i]);
                }
			}
	}
	fim = omp_get_wtime();
	double t_paralelo = fim - inicio;
	printf("Execucao paralela: %f\n",t_paralelo);
	double speedup = t_serial/t_paralelo;
	printf("Speedup: %.4f\n", t_serial/t_paralelo);
	printf("Eficiencia: %.4f\n",speedup/4.0);
}

