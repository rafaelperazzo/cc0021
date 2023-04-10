#include <omp.h>

double cp_elapsed_time(double start_time, double end_time) {
    return end_time - start_time;
}

double cp_speedup(double serial_time, double parallel_time)
{
    return serial_time / parallel_time;
}

double cp_efficiency(double serial_time, double parallel_time, size_t num_threads)
{
    return cp_speedup(serial_time, parallel_time) / num_threads;
}
