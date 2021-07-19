#include <mpi.h>
#include <stdio.h>
#define NINTERVALS  50000000

int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int ncpus;
    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    int meu_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);

    double meupi, h, soma, x,inicio,fim;
    long int i;
    
    inicio = MPI_Wtime();
    h = 1.0 / (double) NINTERVALS;
    soma = 0.0;
    for (i = meu_rank + 1; i <= NINTERVALS; i += ncpus) {
        x = h * ((double) i - 0.5);
        //soma += f(x);
        soma+=4.0 / (1.0 + x * x);
    }
    meupi = h * soma;
    double pi;
    MPI_Reduce(&meupi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (meu_rank == 0) {
        printf("Valor de pi: %f\n",pi);
        fim = MPI_Wtime();
        printf("Tempo de execucao: %f\n",fim-inicio);
    }

    MPI_Finalize();
    return 0;
}