#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100
#define TAMANHO 100000000
#define NUM_THREADS 2

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);
double **gerar_matriz(int linhas, int colunas);
void mostrar_matriz(double **matriz, int linhas, int colunas);
int **gerar_matriz_inteiro(int linhas, int colunas);
void mostrar_matriz_inteiro(int **matriz, int linhas, int colunas);

int main(int argc, char* argv[]) {
    
    if (argc==2) {
        omp_set_num_threads(atoi(argv[1]));
    }
    else {
        omp_set_num_threads(NUM_THREADS);
    }
    
    /*
    INICIO
    */

    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    double tempo_sequencial;
    double tempo_paralelo;
    vetor = gerar_vetor_inteiro(TAMANHO);
    //double **matriz;
    //matriz = gerar_matriz(TAMANHO,TAMANHO);
    
    /*
    CÓDIGO SEQUENCIAL
    */
    double inicio = omp_get_wtime();
    //SEU CÓDIGO SEQUENCIAL
    double fim = omp_get_wtime();
    tempo_sequencial = fim-inicio;
    printf("Tempo sequencial: %.2f\n",tempo_sequencial);

    /*
    CÓDIGO PARALELO
    */

    inicio = omp_get_wtime();
    #pragma omp parallel
    {
        //SEU CÓDIGO PARALELO
    }
    fim = omp_get_wtime();
    tempo_paralelo = fim-inicio;
    printf("Tempo paralelo: %.2f\n",tempo_paralelo);
    double speedup = tempo_sequencial/tempo_paralelo;
    printf("Speedup: %.2f\n",speedup);
    double eficiencia = speedup/omp_get_num_threads();
    printf("Eficiencia: %.2f\n",eficiencia);
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

int **gerar_matriz_inteiro(int linhas, int colunas) {
    int **matriz = (int **) malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % MAX;
        }
    }
    return matriz;
}

void mostrar_matriz_inteiro(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

double **gerar_matriz(int linhas, int colunas) {
    double **matriz = (double **) malloc(linhas * sizeof(double *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double *) malloc(colunas * sizeof(double));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = (rand() / (double)RAND_MAX);
        }
    }
    return matriz;
}

void mostrar_matriz(double **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%.5f ", matriz[i][j]);
        }
        printf("\n");
    }
}