#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 1000000000
#define max  90000000

int achou_s(int n, int *vetor, int inicio, int fim) {
    int i;
    for (i=inicio;i<fim;i++) {
        if (n==vetor[i]) {
            return (1);
        }
    }
    return 0;
}

int achou_p(int n, int *vetor) {
    int i;
    int metade = (int)(TAMANHO/2);
    int achou = 0;
    #pragma omp task
    for (i=0;i<metade;i++) {
        if (!achou) {
            if (n==vetor[i]) {
                achou = 1;
                break;            
            }
        }
    }
    #pragma omp task
    for (i=metade;i<TAMANHO;i++) {
        if (!achou) {
            if (n==vetor[i]) {
                achou = 1;
                break;          
            }
        }
    }
    #pragma omp taskwait
    return (achou);
}


int main () {
    //INICIANDO GERADOR DE NÚMERO ALEATÓRIO
    time_t t;
    srand((unsigned) time(&t));
    //INICIANDO VETOR
    int n  = 1000000003;
    int *vetor;
    vetor = malloc(TAMANHO*sizeof(int));
    int i;
    for (i=0;i<TAMANHO;i++) {
        int num = (rand() % (max+1));
        vetor[i] = num;
    }

    double inicio,fim;
    //EXECUÇÃO SERIAL
    inicio = omp_get_wtime();
    int achou = achou_s(n,vetor,0,TAMANHO);
    fim = omp_get_wtime();
    double t_serial = fim-inicio;
    printf("Execucao serial: %f\n",t_serial);
    
    //EXECUÇÃO PARALELA
    inicio = omp_get_wtime();
	#pragma omp parallel num_threads(2) 
    {
        #pragma omp single 
        {
            achou = achou_p(n,vetor);
        }

    }
	fim = omp_get_wtime();
	double t_paralelo = fim - inicio;
	printf("Execucao paralela: %f\n",t_paralelo);
	double speedup = t_serial/t_paralelo;
	printf("Speedup: %.4f\n", t_serial/t_paralelo);
	printf("Eficiencia: %.4f\n",speedup/2);
}

