#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /*
    INICIO
    */
    int num_steps = 10000000;
    double step;
    int i;
    double x,pi_total,pi_parcial,sum=0;

    step = 1.0/(double)num_steps;

    for (i=rank;i<=num_steps;i+=nprocs) {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }

    pi_parcial = step*sum;

    MPI_Reduce(&pi_parcial,&pi_total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if (rank==0) {
        printf("Valor de pi: %.10f\n",pi_total);
    }

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}
