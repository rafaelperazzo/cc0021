#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 100000000
#define SUBTAMANHO 50000000
#define max  10000

/*
1) Escrever função que dado um vetor, retorne a soma de seus valores
*/
long int soma_vetor(int *vetor, long int tamanho) {

    int i;
    long int soma = 0;
    for (i=0;i<tamanho;i++) {
        soma = soma + vetor[i];
    }
    return (soma);

}

int main(int argc, char** argv) {

    /*
    2) Iniciar as rotinas MPI
    */
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    /*
    3) Iniciar variáveis “locais” de cada processo e as “globais” do rank 0. 
    */
    /*
    Variável de controle
    */
    long int i;
    /*
    Vetores: o vetor completo (controlado pelo rank 0)
    e os subvetores, para todos os processos, inclusive o 0
    */
    int *vetor=NULL,*subvetor=NULL;
    
    /*
    Variáveis para análise de desempenho do processamento, geração e da distribuição. 
    */

    double inicio,fim,inicio_msg,fim_msg,inicio_rand,fim_rand;

    /*
    4) Rank 0 gera o vetor aleatório
    */
    if (rank==0) {
        inicio_rand = MPI_Wtime();
        vetor = malloc(TAMANHO*sizeof(int));
        time_t t;
        srand((unsigned) time(&t));
        for (i=0;i<TAMANHO;i++) {
            int num = (rand() % (max+1));
            vetor[i] = num;
        }
        fim_rand = MPI_Wtime();
        printf("Tempo de geração do vetor aleatório: %f\n",fim_rand-inicio_rand);
    }
    /*
    5) Rank 0 divide o vetor em 2 partes e distribui
    */
    /*
    Cada processo prepara o espaço para armezenar seu subvetor
    */
    subvetor = malloc(SUBTAMANHO*sizeof(int));
    
    if (rank==0) {
        inicio = MPI_Wtime();
    }
    /*
    O processo 0 envia os subvetores para todos os processos, inclusive ele mesmo
    */
    MPI_Scatter(vetor, SUBTAMANHO, MPI_INT, subvetor,SUBTAMANHO, MPI_INT, 0, MPI_COMM_WORLD);
    /*
    6) Cada processo calcula a soma do seu vetor individual
    */
    long int soma=0;
    for (i=0;i<SUBTAMANHO;i++) {
        soma = soma + subvetor[i];
    }
    /*
    7) O processo 0 recebe os resultados
    */
    /*
    O resultado da soma de cada subvetor é devolvido ao rank 0, que armazena em um vetor, indexado
    pelo número do processo. Para isso deve-se criar este vetor previamente, com o tamnho sendo igual
    ao número de processos.
    */
    long int *somas = NULL;
    if (rank==0) {
        somas = malloc((nprocs)*sizeof(long int));
        inicio_msg = MPI_Wtime();
    }
    /*
    Recebendo o resultado de cada soma, e armazenando em somas
    */
    MPI_Gather(&soma, 1, MPI_LONG, somas, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    if (rank==0) {
        fim_msg = MPI_Wtime();
        printf("Tempo de distribuicao: %f\n",fim_msg-inicio_msg);
    }
    /*
    8) O processo 0 consolida e mostra o resultado final
    */
    if (rank==0) {
        /*
        Somando cada soma de cada processo, e consolidando em uma soma total
        */
        long int total=0;
        for (i=0;i<nprocs;i++) {
            total = total + somas[i];
        }
        /*
        Mostrando a média aritmética
        */
        printf("Media: %f\n",total/(double)TAMANHO);
        fim = MPI_Wtime();
        /*
        Relatório de desempenho
        */
        printf("Tempo de execucao: %f\n",fim-inicio);
        double tempo_processamento,tempo_distribuicao,tempo_total_processamento;
        tempo_processamento = fim-inicio;
        tempo_distribuicao = fim_msg-inicio_msg;
        tempo_total_processamento = tempo_processamento+tempo_distribuicao;
        printf("Proporcao do tempo de distribuicao: %f%%\n",(tempo_distribuicao/tempo_total_processamento)*100);
    }
    /*
    Finalizando MPI
    */
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}