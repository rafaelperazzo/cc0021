#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 3
#define COLUNAS 3

void *tarefa(void *linha);

int main() {
    
    int rc1,rc2;

    pthread_t t1,t2;

    int i = 0;

    rc1 = pthread_create(&t1, NULL, tarefa, &i);
    i++;
    rc2 = pthread_create(&t2, NULL, tarefa, &i);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}


void *tarefa(void *linha) {
    int i = *((int *) linha);
    printf("%d\n",i);
}