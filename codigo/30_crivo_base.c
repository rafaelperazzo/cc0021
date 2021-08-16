
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

//FALTA COLOCAR AS DIRETIVAS DO OPENMP
int eratosthenes(int lastNumber, int threads)
{
  
  omp_set_num_threads(threads);

  //PASSO 1
  char *isPrime = (char*)malloc((lastNumber+1)*sizeof(char));
  const int lastNumberSqrt = (int)sqrt((double)lastNumber);
  #pragma omp parallel for
    for (int i = 0; i <= lastNumber; i++)
        isPrime[i] = 1;
  
  //PASSO 2
  #pragma omp parallel for schedule(dynamic)
    for (int i = 2; i<= lastNumberSqrt; i++)
        if (isPrime[i])
        for (int j = i*i; j <= lastNumber; j += i)
            isPrime[j] = 0;
  //PASSO 3
  int found = 0;
  #pragma omp parallel for reduction(+:found)
    for (int i = 2; i <= lastNumber; i++)
        found += isPrime[i];
  
  //FINALIZANDO
  free(isPrime);
  return found;
}

int main() {
    char *filename = "resultados.dat";
    FILE *fp = fopen(filename, "w");
    fprintf(fp,"%s;%s;%s;%s\n","N","threads","Tempo","Total");
    int threads = 2;
    int maximo = 1000000000;
    int inicio = 100000000;
    int step = 200000000;
    
    for (int i=inicio;i<=maximo;i+=step) { //i -> limites
        for (int j=1;j<=threads;j++) { //j-> threads
            double inicio = omp_get_wtime();
            int total = 0;
            total = eratosthenes(i,j);
            double fim = omp_get_wtime();
            printf("%d %d %f %d\n",i,j,fim-inicio,total);
            fprintf(fp,"%d;%d;%f;%d\n",i,j,fim-inicio,total);
        }
    }
    fclose(fp);
    return 0;
}