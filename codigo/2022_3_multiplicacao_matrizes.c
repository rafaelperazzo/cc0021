#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define LINHAS 2000
#define COLUNAS 2000
#define MAX 100

int **gerar_matriz(int linhas, int colunas, int threads);
int *gerar_vetor(int n, int threads);
int **gerar_matriz_vazia(int linhas, int colunas, int threads);
int **mostrar(int linhas, int colunas, int **m);
int **multiplicar(int linhas, int colunas, int **a, int **b);

int main() {
   int n_procs = omp_get_num_procs();
   int n_threads = (int)(n_procs/2.0);
   int **a = gerar_matriz(LINHAS,COLUNAS,n_threads);
   int **b = gerar_matriz(LINHAS,COLUNAS,n_threads);
   double inicio = omp_get_wtime();
   int **c = multiplicar(LINHAS,COLUNAS,a,b);
   double fim = omp_get_wtime();
   printf("Tempo: %.4f\n",fim-inicio);
}
    
int **gerar_matriz(int linhas, int colunas, int threads){
    time_t t;
    int i,j;
    srand((unsigned) time(&t));
    //ALOCANDO A MATRIZ
    int **a = (int **)malloc(linhas * sizeof(int*));
    #pragma omp parallel num_threads(threads) 
    {
        #pragma omp for
        for(int i = 0; i < linhas; i++) a[i] = (int *)malloc(colunas * sizeof(int));
    }
    
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for (i=0;i<linhas;i++) {
            for (j=0;j<colunas;j++) {
                int num = (rand() % (MAX+1));
                a[i][j] = num;
            }
        }
    }
    
    return (a);
}

int **gerar_matriz_vazia(int linhas, int colunas, int threads){
    int i,j;
    //ALOCANDO A MATRIZ
    int **a = (int **)malloc(linhas * sizeof(int*));
    #pragma omp parallel num_threads(threads) 
    {
        #pragma omp for
        for(int i = 0; i < linhas; i++) a[i] = (int *)malloc(colunas * sizeof(int));
    }
    return (a);
}

int *gerar_vetor(int n, int threads) {
    int *vetor;
    int i;
    vetor = malloc(n*sizeof(int));
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for (i=0;i<n;i++) {
            int num = (rand() % (MAX+1));
            vetor[i] = num;
        }
    }
    return vetor;
}

int **multiplicar(int linhas, int colunas, int **a, int **b){
    int i,j,k;
    //ALOCANDO A MATRIZ
    int **c = (int **)malloc(linhas * sizeof(int*));
    for(int i = 0; i < linhas; i++) c[i] = (int *)malloc(colunas * sizeof(int));
    int soma;
    for (i=0;i<linhas;i++) {
        for (j=0;j<colunas;j++) {
            soma = 0;
            for (k=0;k<linhas;k++) {
                soma = soma + a[i][k] + b[k][j];    
            }
            c[i][j] = soma;
        }
    }

    return (c);
}