#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
    int n = 10;
    int *y;
    int i;
    int x;
    y = malloc(n*sizeof(int));

    x= 1;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp for firstprivate(x)
        for(i = 0; i < n; i++){
            y [i] = x + i;
            x = i;
        }
    }
    

    for(i = 0; i < n; i++){
        printf("y[%d]=%d\n",i,y[i]);
    }

    return 0;
}