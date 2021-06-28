#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define num_steps 300000000

int main() {
    double step;
    double pi, inicio, fim;
    int t = omp_get_num_threads();
    /*
    VERSÃO PARALELA
    */
    pi = 0;
    inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    #pragma omp parallel num_threads(4)
    {
        double x,sum=0.0;
        int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for (i=id,sum=0.0;i< num_steps; i=i+nthrds){
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x*x);
        }
        #pragma omp critical
            pi+=sum*step;
    }
    fim = omp_get_wtime();
    double t_paralelo = fim-inicio;
    printf("Pi: %f\n",pi);
    printf("Execucao paralela(s): %f\n",t_paralelo);
    return 0;
}
