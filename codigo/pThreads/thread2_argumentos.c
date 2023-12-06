#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct argumentos
{
    /* data */
    int valor1;
    float valor2;
};

void *tarefa();

int main()
{
    pthread_t thread1, thread2;
    int  iret1, iret2;
    struct argumentos args1,args2;

    args1.valor1 = 10;
    args1.valor2 = 20.5;

    args2.valor1 = 234;
    args2.valor2 = 17.5;

    iret1 = pthread_create( &thread1, NULL, tarefa, (void*) &args1);
    iret2 = pthread_create( &thread2, NULL, tarefa, (void*) &args2);

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 

    return (0);
}

void *tarefa(void *args)
{
     int i;
     for (i=1;i<=1000000000;i++) {

     }
     printf("%d\n", ((struct argumentos *)args)->valor1);
     printf("%f\n", ((struct argumentos *)args)->valor2);
}
