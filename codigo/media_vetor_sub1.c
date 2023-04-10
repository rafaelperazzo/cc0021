/**
 * Escreva um programa sequencial paralelo em C com OpenMP, que calcula a média aritmética de um vetor com 500.000.000 (quinhentos milhões) de elementos aleatórios. Os valores variam entre 1 e 100.000. Calcule o speedup e eficiência do seu programa.
 *  
 * Write a parallel sequel program in C with OpenMP, that calculates the math average of a vector with 500.000.000 (five millions) random elements. The values range from 1 to 100.000. Calculates the speedup and effiency of your program.
 */

#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "benchmark.c"

#define CP_NUMBER_THREADS 2
// #define CP_VECTOR_MAX_SIZE 500000000
#define CP_VECTOR_MAX_SIZE 100000000
#define CP_VECTOR_MIN_VALUE 100000
#define CP_VECTOR_MAX_VALUE 1

/** Prints a cp_vector
 * Todo: refactor the code to concatenate all array values into a single string and print it.
 */
void cp_print_vector(float *vector)
{
    printf("[");

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for
        for(size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            printf("%10.2f,", vector[i]);
        }
    }

    printf("]\n");
}

/** Returns a random vector
 * int min: min value accepted in the vector
 * int max: max value accepted in the vector
 */
float *cp_random_vector(int min, int max)
{
    float *vector = (float *) malloc(sizeof(float) * CP_VECTOR_MAX_SIZE);

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        srand(time(NULL));

        #pragma omp for
        for (size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            vector[i] = (rand() % (max - min + 1)) + min;
        }
    }

    return vector;
}

/** Calculates an average of all values in a vector
 * 
 */
double cp_vector_average(float *vector)
{
    double sum = 0;

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for reduction(+: sum)
        for (size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            sum += vector[i];
        }
    }

    return sum / (float) CP_VECTOR_MAX_SIZE;
}

double cp_serial_average(float *vector)
{
    double sum = 0;

    for (size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
    {
        sum += vector[i];
    }

    return sum / (float) CP_VECTOR_MAX_SIZE;
}

int main()
{
    float *vector;
    double average, parallel_elapsed_time, parallel_start_time, parallel_end_time,  serial_elapsed_time, serial_start_time, serial_end_time;

    vector = cp_random_vector(CP_VECTOR_MIN_VALUE, CP_VECTOR_MAX_VALUE);

    // Parallel
    parallel_start_time = omp_get_wtime();
    average = cp_vector_average(vector);
    parallel_end_time = omp_get_wtime();
    parallel_elapsed_time = cp_elapsed_time(parallel_start_time, parallel_end_time);
    printf("parallel average: %.2f elapsed time: %.1lf seconds\n", average, parallel_elapsed_time);

    // Serial
    serial_start_time = omp_get_wtime();
    average = cp_serial_average(vector);
    serial_end_time = omp_get_wtime();
    serial_elapsed_time = cp_elapsed_time(serial_start_time, serial_end_time);
    printf("serial average: %.2f elapsed time: %.1lf seconds\n", average, serial_elapsed_time);


    // Conclusion
    printf("speedup: %.2lf, efficiency: %.2lf\n", cp_speedup(serial_elapsed_time, parallel_elapsed_time), cp_efficiency(serial_elapsed_time, parallel_elapsed_time, CP_NUMBER_THREADS));

    return 0;
}