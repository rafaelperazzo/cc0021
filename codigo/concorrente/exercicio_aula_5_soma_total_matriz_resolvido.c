/*
Escreva um programa que realize o cálculo das somas dos valores das linhas de uma matriz qualquer de 
números inteiros e imprima o somatório total na tela. 
Faça com que o cálculo do somatório de cada linha seja realizado concorrentemente por uma thread. 

A soma de cada linha deve ser adicionada a uma variável compartilhada entre as threads.

O resultado deve ser a soma total da matriz. 
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 3
#define COLUNAS 3

int **gerar_matriz(int linhas, int colunas);
void mostrar_matriz(int **matriz, int linhas, int colunas);
void *tarefa(void *linha);

int **matriz;
int soma = 0;
pthread_mutex_t trava; //TRAVA PARA REGIÃO CRÍTICA - global


int main() {
    
    srand(time(NULL));
    pthread_mutex_init(&trava, NULL); //INICIALIZA A TRAVA
    matriz = gerar_matriz(LINHAS, COLUNAS);
    int rc;
    mostrar_matriz(matriz, LINHAS, COLUNAS);

    pthread_t threads[LINHAS];

    int linhas[LINHAS];
    for (int i=0; i<LINHAS; i++) {
        linhas[i] = i;
    }

    int i;

    for (i=0; i<LINHAS; i++) {
        rc = pthread_create(&threads[i], NULL, tarefa, &linhas[i]);
    }

    for (int i=0; i<LINHAS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Soma total: %d\n", soma);
    pthread_mutex_destroy(&trava); //DESTROI A TRAVA
    free(matriz);
    return 0;
}

int **gerar_matriz(int linhas, int colunas) {
    int **matriz = (int **) malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
    return matriz;
}

void mostrar_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void *tarefa(void *linha) {
    int soma_linha = 0;
    int LINHA = *(int*)linha;
    printf("Linha --->: %d\n", LINHA);
    for (int j = 0; j < COLUNAS; j++) {
        soma_linha += matriz[LINHA][j];
    }
    pthread_mutex_lock(&trava);
    //REGIÃO CRÍTICA - APENAS UMA THREAD DEVE ACESSAR POR VEZ
    soma = soma + soma_linha;
    pthread_mutex_unlock(&trava);
}