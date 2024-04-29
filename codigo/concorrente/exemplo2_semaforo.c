#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaforo;

void *tarefa(void *arg) {
    int thread_id = *((int *)arg);
    
    sem_wait(&semaforo);

    printf("(%d) Acessando região crítica...\n",thread_id);
    sleep(rand() % 8);
    
    printf("(%d) Saindo da região crítica...\n",thread_id);
    sem_post(&semaforo);
}

int main() {

    pthread_t threads[10];
    sem_init(&semaforo, 0, 1); // Inicializa o semáforo com 1 (disponível)
    
    int *threads_ids[10];
    for (int i=0; i<10; i++) {
        threads_ids[i] = malloc(sizeof(int));
        *threads_ids[i] = i;
        pthread_create(&threads[i], NULL, tarefa, (void *)threads_ids[i]);
    }

    for (int i=0; i<10; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaforo);
    return 0;
}