/*
Escreva um programa em C, com OpenMP, que calcule o vetor c=a*b de dois vetores com 100.000.000 de elementos aleatórios (entre 0 e 50).

Versão sequencial, calculando o tempo de execução
Versão paralela, com 2 threads, calculando o tempo de execução
Speedup
Eficiência
Tudo em um único arquivo.
Utilize o arquivo disponível abaixo como modelo

https://github.com/rafaelperazzo/cc0021/blob/master/codigo/concorrente/template_openMP.c
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 25
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    int *a = NULL;
    int *b = NULL;
    int *c = NULL;
    a = gerar_vetor_inteiro(TAMANHO);
    b = gerar_vetor_inteiro(TAMANHO);
    c = (int *)malloc(sizeof(int) * TAMANHO);
    
    int i;
    
    //SEQUENCIAL
    double inicio = omp_get_wtime();
    for (i=0;i<TAMANHO;i++) {
        c[i] = a[i] * b[i];
    }
    double fim = omp_get_wtime();
    printf("Tempo sequencial: %.5f\n",fim-inicio);
    double tempo_sequencial = fim-inicio;
    //PARALELO
    inicio = omp_get_wtime();
    int num_threads = omp_get_num_procs()/2;
    printf("Numero de threads: %d\n",num_threads);
    #pragma omp parallel for num_threads(num_threads)
    for (i=0;i<TAMANHO;i++) {
        c[i] = a[i] * b[i];
    }
    fim = omp_get_wtime();
    printf("Tempo paralelo: %.5f\n",fim-inicio);
    double tempo_paralelo = fim-inicio;
    double speedup = tempo_sequencial / tempo_paralelo;
    printf("Speedup: %.5f\n",speedup);
    printf("Eficiencia: %.5f\n",speedup/num_threads);
    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}
