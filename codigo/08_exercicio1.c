#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main() {

    long int n,divisores=0;
    printf("Digite n: ");
    scanf("%ld",&n);
    long int i;
    double inicio,fim,t_serial,t_paralelo;
    int limite = (int)(n/2);
    inicio = omp_get_wtime();
    for (i=2;i<limite;i++) {
        if ((n%i)==0) {
            divisores++;
        }
    }
    fim = omp_get_wtime();
    if (divisores==0) {
        printf("Primo\n");
    }
    else {
        printf("Nao primo: %ld divisores\n",divisores);
    }
    t_serial = fim-inicio;


    //VERSÃO PARALELA
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(2)
    {
        #pragma omp for reduction (+:divisores)
        for (i=2;i<limite;i++) {
            if ((n%i)==0) {
                divisores++;
            }
        }
    }

    fim = omp_get_wtime();
    t_paralelo = fim-inicio;
    printf("**********************************************\n");
    printf("ANALISE DE DESEMPENHO EM C\n");
    printf("**********************************************\n");
    printf("Tempo de execucao sequencial: %f\n",t_serial);
    printf("Tempo de execucao paralelo: %f\n",t_paralelo);
    double speedup = t_serial/t_paralelo;
    double eficiencia = speedup/2.0;
    printf("Speedup: %f\n",speedup);
    printf("Eficiencia: %f\n",eficiencia);

    return 0;

}
