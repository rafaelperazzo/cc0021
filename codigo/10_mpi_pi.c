#include <stdio.h>
#include <math.h>
#include <mpi.h> 
#define NINTERVALS  10000
  
 
double f(double a){
    return (4.0 / (1.0 + a * a));
}
 
 int main(int argc, char *argv[]) {
    int myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
                
    startwtime = MPI_Wtime();
    
    h = 1.0 / (double) NINTERVALS;
    sum = 0.0;
    
    for (i = myid + 1; i <= NINTERVALS; i += numprocs) {
        x = h * ((double) i - 0.5);
        sum += f(x);
    }
    mypi = h * sum;
    
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myid == 0) {
        printf("pi is approximately %.16f, Error is %.16f\n",pi, fabs(pi - PI25DT));
        endwtime = MPI_Wtime();
        printf("wall clock time = %f\n", endwtime - startwtime);
    }
    
    MPI_Finalize();
    return 0;
}