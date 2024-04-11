#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void *tarefa(void *linha);

pthread_mutex_t trava;
int shared = 0;

int main() {
    
    int rc1,rc2;

    pthread_t t1,t2;

    int i = 0;

    pthread_mutex_init(&trava, NULL);

    rc1 = pthread_create(&t1, NULL, tarefa, &i);
    rc2 = pthread_create(&t2, NULL, tarefa, &i);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("%d\n",shared);
    
    pthread_mutex_destroy(&trava);
    return 0;
}


void *tarefa(void *linha) {
    int i = *((int *) linha);
    pthread_mutex_lock(&trava);
    shared++;
    printf("%d\n",shared);
    pthread_mutex_unlock(&trava);
}