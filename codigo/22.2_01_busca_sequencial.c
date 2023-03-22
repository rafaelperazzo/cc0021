#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000000

float *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    float *vetor = NULL;
    vetor = gerar_vetor(MAX);

    double inicio,fim;
    int i;
    float n = 0.38747;
    //EXECUÇÃO SEQUENCIAL
    inicio = omp_get_wtime();
    for (i=0;i<MAX;i++) {
        if (vetor[i]==n) {
            printf("Thread[%d] ACHOU: %.4f\n", omp_get_thread_num(),vetor[i]);
        }
    }
    fim = omp_get_wtime();
    double t_serial = fim-inicio;
    printf("Execução sequencial: %f\n",t_serial);
    //EXECUÇÃO PARALELA
    inicio = omp_get_wtime();
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for
			for (i=0;i<MAX;i++) {
                if (vetor[i]==n) {
                    printf("Thread[%d] ACHOU: %.4f\n", omp_get_thread_num(),vetor[i]);
                }
			}
	}
	fim = omp_get_wtime();
	double t_paralelo = fim - inicio;
	printf("Execução paralela: %f\n",t_paralelo);
	double speedup = t_serial/t_paralelo;
	printf("Speedup: %.4f\n", t_serial/t_paralelo);
	printf("Eficiência: %.4f\n",speedup/2.0);


    /*
    FIM
    */
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}
    
    