/*
Escreva um programa em C, com OpenMP, que calcule a média aritmética de um vetor com 100.000.000 de elementos aleatórios (entre 0 e 50).

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
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    
    int i;
    double soma = 0;
    
    //SEQUENCIAL
    double inicio = omp_get_wtime();
    for (i=0;i<TAMANHO;i++) {
        soma = soma + vetor[i];    
    }
    double media = soma / (double)TAMANHO;
    double fim = omp_get_wtime();
    printf("Media: %.5f\n",media);
    printf("Tempo sequencial: %.5f\n",fim-inicio);
    double tempo_sequencial = fim-inicio;

    //PARALELO
    soma = 0;
    inicio = omp_get_wtime();
    int num_threads = omp_get_num_procs()/2;
    printf("Numero de threads: %d\n",num_threads);
    #pragma omp parallel for reduction(+:soma) num_threads(num_threads)
    for (i=0;i<TAMANHO;i++) {
        soma = soma + vetor[i];    
    }
    media = soma / (double)TAMANHO;
    fim = omp_get_wtime();
    printf("Media: %.5f\n",media);
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
