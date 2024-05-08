#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 1000000000

int main() {

    double inicio = omp_get_wtime();
    double step = 1.0/(double) NUM_STEPS;
    double sum = 0.0;

    for (int i = 0; i < NUM_STEPS; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double fim = omp_get_wtime();
    double pi = step * sum;

    printf("Valor aproximado de pi: %f\n", pi);
    printf("Tempo de execução: %.2f segundos \n", fim - inicio);
    return 0;
}