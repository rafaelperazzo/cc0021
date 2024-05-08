#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_STEPS 1000000000
#define NUM_THREADS 2

int main(int argc, char* argv[]) {

    if (argc==2) {
        omp_set_num_threads(atoi(argv[1]));
    }
    else {
        omp_set_num_threads(NUM_THREADS);
    }

    double step = 1.0/(double) NUM_STEPS;
    double sum = 0.0;
    
    double inicio = omp_get_wtime();
    #pragma omp parallel
    {        
        double local_sum = 0;
        #pragma omp for
        for (int i=0; i<NUM_STEPS; i++) {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        {
            sum += local_sum;
        }
    }
    double pi = step * sum;
    double fim = omp_get_wtime();

    printf("Valor aproximado de pi: %f\n", pi);
    printf("Tempo de execução: %f\n", fim-inicio);
    return 0;
}