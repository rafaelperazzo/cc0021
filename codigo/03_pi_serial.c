#include <stdio.h>
#include <omp.h>

int main() {

    static long num_steps = 100000000;
    double step;
    int i; double x, pi, sum = 0.0;
    int t = omp_get_num_threads();
    printf("Theads: %d\n",t);
    double inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    for (i=0;i< num_steps; i++){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo
    }
    pi = step * sum;
    double fim = omp_get_wtime();
    printf("%.5f\n",pi);
    printf("%f\n",fim-inicio);
    return 0;
}
