/*
https://docs.google.com/presentation/d/1YFNNH4ay4hk8emSrDKxuy9FngO7L6-wjnRYtyPDyyyQ/edit?usp=drive_link

Escreva um programa em C, com Pthreads, que calcule a média aritmética de um vetor com 10.000.000 de elementos inteiros. A tarefa deve ser realizada por 2 threads paralelas. 

Assuntos a serem exercitados:

Criação de threads
Mutex
Passagem de argumentos para threads com structs

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

#define MAX 100
#define TAMANHO 10000000
#define NTHREADS 2

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);
void *tarefa(void *argumentos);
double media_sequencial(int *vetor,int tamanho);

struct dados{
    int  inicio;
    int  quantidade;
};

//VARIÁVEIS COMPARTILHADAS
int *vetor = NULL;
double soma = 0; 
pthread_mutex_t trava;

int main() {
    /*
    INICIO
    */
    srand(time(NULL));
    pthread_mutex_init(&trava, NULL);
    
    vetor = gerar_vetor_inteiro(TAMANHO);

    struct dados vetor_dados[NTHREADS];
    pthread_t threads[NTHREADS];
    int i;
    
    for (i=0;i<NTHREADS;i++) {
        vetor_dados[i].inicio = (i * (int)((TAMANHO/(double)NTHREADS)));
        vetor_dados[i].quantidade = (int)(TAMANHO/(double)NTHREADS);
        if (i == NTHREADS-1) {
            vetor_dados[i].quantidade = TAMANHO - vetor_dados[i].inicio;
        }
        pthread_create(&threads[i], NULL, tarefa, &vetor_dados[i]);
    }

    for (i=0;i<NTHREADS;i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&trava);
    printf("Média: %.6f\n",soma/(double)TAMANHO);
    assert((soma/(double)TAMANHO) == media_sequencial(vetor,TAMANHO));
    free(vetor);
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
        double num = (rand() / (double)RAND_MAX);
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

void *tarefa(void *argumentos) {
    struct dados *dados = (struct dados *)argumentos;
    int inicio = dados->inicio;
    int quantidade = dados->quantidade;
    int fim = inicio + quantidade;
    double soma_parcial = 0;
    for (int i=inicio;i<fim;i=i+1) {
        soma_parcial = soma_parcial + vetor[i];
    }
    pthread_mutex_lock(&trava);
    soma = soma + soma_parcial;
    pthread_mutex_unlock(&trava);
}

double media_sequencial(int *vetor,int tamanho) {
    double soma = 0;
    for (int i=0;i<tamanho;i++) {
        soma = soma + vetor[i];
    }
    return(soma/(double)tamanho);
}