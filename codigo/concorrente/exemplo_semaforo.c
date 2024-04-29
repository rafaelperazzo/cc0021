#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaforo;

void *tarefa(void *arg) {
    int thread_id = *((int *)arg);
    printf("(%d) Aguardando liberação do semáforo...\n",thread_id);
    sem_wait(&semaforo);
    printf("(%d) Acessando região crítica...\n",thread_id);
    sleep(rand() % 8);
    printf("(%d) Saindo da região crítica...\n",thread_id);
    sem_post(&semaforo);
}

int main() {

    pthread_t thread1, thread2;
    sem_init(&semaforo, 0, 1); // Inicializa o semáforo com 1 (disponível)
    int id1 = 1, id2 = 2;
    pthread_create(&thread1, NULL, tarefa, &id1);
    pthread_create(&thread2, NULL, tarefa, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaforo);
    return 0;
}