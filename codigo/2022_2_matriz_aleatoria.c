#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define LINHAS 100
#define COLUNAS 100
#define MAX 100

int **gerar_matriz(int linhas, int colunas, int threads);
int *gerar_vetor(int n, int threads);
int **gerar_matriz_vazia(int linhas, int colunas, int threads);

int main() {
   int n_procs = omp_get_num_procs();
   int n_threads = (int)(n_procs/2.0);
   int **a = gerar_matriz(LINHAS,COLUNAS,n_threads);
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