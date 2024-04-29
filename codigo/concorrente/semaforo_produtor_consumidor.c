#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 8
#define NUM_CONSUMERS 6

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, empty, full;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produz um item
        sem_wait(&empty); // Espera o buffer não estar cheio
        sem_wait(&mutex); // Bloqueia o acesso ao buffer
        buffer[in] = item;
        printf("Produzido: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Atualiza o índice de inserção
        sem_post(&mutex); // Libera o acesso ao buffer
        sem_post(&full); // Indica que há um item no buffer
        sleep(rand() % 4); // Simula tempo de produção
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full); // Espera o buffer não estar vazio
        sem_wait(&mutex); // Bloqueia o acesso ao buffer
        item = buffer[out];
        printf("Consumido: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Atualiza o índice de remoção
        sem_post(&mutex); // Libera o acesso ao buffer
        sem_post(&empty); // Indica que há um espaço vazio no buffer
        sleep(rand() % 4); // Simula tempo de consumo
    }
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
