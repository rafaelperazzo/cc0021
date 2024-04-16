/*
https://docs.google.com/presentation/d/1LY1nRXSCTO_lKa5wQofV6avb6oKK6_TePzF1goZTmbk/edit#slide=id.g2cb3969faa5_0_22

Criar 4 threads que multipliquem todos os elementos de um vetor por um escalar e depois achem o maior elemento. 
Primeiro fazem a multiplicação e depois acham o maior.
Utilize o código base:
https://github.com/rafaelperazzo/cc0021/blob/master/codigo/concorrente/template_vetor.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 100
#define TAMANHO 10

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);
void *tarefa(void *argumentos);

struct dados{
    int  inicio;
    int  quantidade;
    int  escalar;
};

int *vetor = NULL;

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    
    vetor = gerar_vetor_inteiro(TAMANHO);
    //mostrar_vetor_inteiro(vetor,TAMANHO);

    struct dados vetor_dados[4];
    pthread_t threads[4];
    int i;
    for (i=0;i<4;i++) {
        vetor_dados[i].inicio = (int)(i * (TAMANHO/4));
        vetor_dados[i].quantidade = (int)(TAMANHO/4);
        vetor_dados[i].escalar = 2;
        pthread_create(&threads[i], NULL, tarefa, &vetor_dados[i]);
    }

    for (i=0;i<4;i++) {
        pthread_join(threads[i], NULL);
    }

    //mostrar_vetor_inteiro(vetor,TAMANHO);
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

void *tarefa(void *argumentos) {
    struct dados *dados = (struct dados *)argumentos;
    int inicio = dados->inicio;
    int quantidade = dados->quantidade;
    int fim = inicio + quantidade;
    int escalar = dados->escalar;
    for (int i=inicio;i<fim;i++) {
        vetor[i] = vetor[i] * escalar;
    }
}