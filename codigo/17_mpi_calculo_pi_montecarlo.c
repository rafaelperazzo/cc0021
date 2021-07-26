#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    const long long iternum=1000000000;
    long long soma=0;
    double x,y,pi,inicio,fim;
    long long i;
    
    inicio = MPI_Wtime();
    srand((unsigned)time(0));
    for(long long i=rank;i<iternum;i=i+nprocs){
        x=(double)rand()/RAND_MAX;
        y=(double)rand()/RAND_MAX;
        if(x*x+y*y<1) 
            ++soma;
    }
    long long soma_geral;
    MPI_Reduce(&soma, &soma_geral, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0) {
        fim = MPI_Wtime();
        pi=(4.0*soma_geral)/(double)iternum;
        printf("Aproximacao de pi: %f\n",pi);
        printf("Tempo de execucao total (%d processo(s)): %f\n",nprocs,fim-inicio);
    }
    /*
    FIM DO CÓDIGO MPI
    */
    MPI_Finalize();
    return 0;
}