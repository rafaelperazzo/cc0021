#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *tarefa();

int main()
{
     pthread_t thread1, thread2;
     int  iret1, iret2;

     iret1 = pthread_create( &thread1, NULL, tarefa, NULL);
     iret2 = pthread_create( &thread2, NULL, tarefa, NULL);

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     return (0);
}

void *tarefa()
{
     int i;
     for (i=1;i<=1000000000;i++) {

     }
}
