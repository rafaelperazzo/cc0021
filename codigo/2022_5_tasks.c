#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main() {

    #pragma omp parallel 
    {
        #pragma omp single
        {
            #pragma omp task 
            {
                printf("Primeira task...\n");
                sleep(5);
                printf("Primeira task finalizada...\n");
            }
            #pragma omp task 
            {
                printf("Segunda task ...\n");
                sleep(7);
                printf("Segunda task finalizada...\n");
            }
            printf("Continuando trabalho na thread single...\n");
        }
    }
    printf("Fim das task paralelas...\n");

    return 0;
    
}