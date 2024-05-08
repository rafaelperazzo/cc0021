#include <stdio.h>
#include <omp.h>

int main() {

    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for (int i=0;i<1000000000; i++) {
            // do something
        }
    }
    double fim = omp_get_wtime();
    printf("Tempo de execução: %f\n", fim-inicio);
    return 0;
}