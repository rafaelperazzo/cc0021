#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

double *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);

int main() {
    /*
    INICIO
    */
    int MAX = 2000000000;
    time_t t;
    srand(time(NULL));
    double *vetor = NULL;
    vetor = gerar_vetor(MAX);
    int i;
    double soma = 0.0;
    double inicio,fim;

    inicio = omp_get_wtime();
    //INÍCIO DO PROCESSAMENTO SEQUENCIAL
    for (i=0;i<MAX;i++) {
        soma = soma + vetor[i];
        
    }
    //FIM DO PROCESSAMENTO SEQUENCIAL
    fim = omp_get_wtime();
    double media = soma/(double)MAX;
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double tempo_s = fim-inicio;
    printf("Tempo sequencial: %lf\n",tempo_s);

    soma = 0;
    inicio = omp_get_wtime();
    //INICIO DO PROCESSAMENTO PARALELO
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
            for (i=0;i<MAX;i++) {
                soma = soma + vetor[i];
            }
    }
    //FIM DO PROCESSAMENTO PARALELO
    fim = omp_get_wtime();
    media = soma/(double)MAX;
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double tempo_p = fim-inicio;
    printf("Tempo paralelo: %.4f\n",tempo_p);
    double speedup = tempo_s/tempo_p;
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiência: %f\n",eficiencia);
    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (double)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}