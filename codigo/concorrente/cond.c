#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *tarefa(void *linha);
void *tarefa2(void *linha);
void *tarefa3(void *linha);

pthread_mutex_t trava;
pthread_cond_t cond;
int shared = 0;

int main() {

    int rc1,rc2;

    pthread_t t1,t2;

    pthread_mutex_init(&trava, NULL);
    int tempo1 = 2;
    int tempo2 = 5;
    rc1 = pthread_create(&t1, NULL, tarefa2, &tempo1);
    rc2 = pthread_create(&t2, NULL, tarefa3, &tempo1);


    pthread_mutex_lock(&trava);
    while (shared<2) {
        printf("shared=%d\n",shared);
        pthread_cond_wait(&cond,&trava);
        printf("Recebido sinal...\n");

    }
    pthread_mutex_unlock(&trava);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("%d\n",shared);
    
    pthread_mutex_destroy(&trava);
    pthread_cond_destroy(&cond);

    return 0;
}

void *tarefa(void *linha) {
    int tempo = *((int *) linha);
    sleep(tempo);
    pthread_mutex_lock(&trava);
    shared++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&trava);
    printf("Finalizada thread\n");
}

void *tarefa2(void *linha) {
    int tempo = *((int *) linha);
    printf("Iniciada thread 2...\n");
    sleep(tempo);
    pthread_mutex_lock(&trava);
    shared++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&trava);
    printf("Finalizada threa 2\n");
}

void *tarefa3(void *linha) {
    int tempo = *((int *) linha);
    printf("Iniciada thread 3...\n");
    sleep(tempo);
    pthread_mutex_lock(&trava);
    shared++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&trava);
    printf("Finalizada thread 3\n");
}