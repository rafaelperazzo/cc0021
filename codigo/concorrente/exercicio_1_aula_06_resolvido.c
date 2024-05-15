#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 100
#define TAMANHO 10000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);
void *tarefa(void *argumentos);

int *vetor = NULL;

struct dados{
    int  inicio;
    int  quantidade;
};

double soma = 0;

pthread_mutex_t trava; //TRAVA PARA REGIÃO CRÍTICA - global

int main() {
    /*
    INICIO
    */
    time_t t;
    srand(time(NULL));
    pthread_mutex_init(&trava, NULL); //INICIALIZA A TRAVA

    vetor = gerar_vetor_inteiro(TAMANHO);
    
    struct dados vetor_dados[2];
    pthread_t threads[2];

    for (int i=0;i<2;i++) {
        vetor_dados[i].inicio = (int)(i * (TAMANHO/2));
        vetor_dados[i].quantidade = (int)(TAMANHO/2);
        pthread_create(&threads[i], NULL, tarefa, &vetor_dados[i]);
    }

    for (int i=0;i<2;i++) {
        pthread_join(threads[i], NULL);
    }
    double media = soma/(double)TAMANHO;
    printf("Media: %.5lf\n", media);
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
    int soma_parcial = 0;
    for (int i=inicio;i<fim;i++) {
        soma_parcial = soma_parcial + vetor[i];
    }
    pthread_mutex_lock(&trava);
    soma = soma + soma_parcial;
    pthread_mutex_unlock(&trava);
}