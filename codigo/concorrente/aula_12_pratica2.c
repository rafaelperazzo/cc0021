/*
EXERCÍCIO DA AULA 12
PRÁTICA 02
https://docs.google.com/presentation/d/1vneTzQgl9DFdfz0Rh9YNLljpAznvXA-WfkiX-RFeXhA/edit#slide=id.g1ff6eca0949_0_0
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

#define THREAD_NUM 2
#define N 100000

struct parametros {
    int id;
    int inicio;
    int fim;
    double h;
};

double somas[THREAD_NUM];

void *calcular_soma(void *arg) {
    struct parametros *p = (struct parametros *)arg;
    double soma = 0;
    double x_i;
    double f_x_i;
    for (int i=p->inicio;i<p->fim;i++) {
        x_i = i*p->h;
        f_x_i = 4/(1+x_i*x_i);
        soma += f_x_i;
    }
    somas[p->id] = soma;
}

int main() {
    int a=0,b=1;
    double h = (b-a)/(double)N;
    pthread_t threads[THREAD_NUM];
    struct parametros vetor_parametros[THREAD_NUM];

    //Zerando a soma de cada thread
    for (int i=0;i<THREAD_NUM;i++) {
        somas[i] = 0;
    }
    //Iniciando as threads
    int particao = (int)(N/THREAD_NUM);
    int inicio = 1;
    for (int i=0;i<THREAD_NUM;i++) {
        vetor_parametros[i].id = i;
        vetor_parametros[i].inicio = inicio;
        vetor_parametros[i].fim = inicio+particao;
        vetor_parametros[i].h = h;
        if (vetor_parametros[i].fim>N) {
            vetor_parametros[i].fim = N;
        }
        if (i==THREAD_NUM-1) {
            vetor_parametros[i].fim = N;
        }
        inicio = vetor_parametros[i].fim;
        pthread_create(&threads[i], NULL, calcular_soma, &vetor_parametros[i]);
    }

    for (int i=0;i<THREAD_NUM;i++) {
        pthread_join(threads[i], NULL);
    }

    double pi = 0;
    for (int i=0;i<THREAD_NUM;i++) {
        pi += somas[i];
    }
    double f_0,f_1;
    f_0 = 4/(1+a*a);
    f_1 = 4/(1+b*b);
    pi = h/(double)2*(f_0 + 2*pi + f_1);
    printf("PI: %.10lf\n",pi);
    
    return 0;
}