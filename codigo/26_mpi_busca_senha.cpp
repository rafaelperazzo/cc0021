#include <bits/stdc++.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
//#include <string>
#include <mpi.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <openssl/sha.h>
#include <cstring>


using namespace std;

// Recursive helper function, adds/removes characters
// until len is reached
void generate(char* arr, int i, string s, int len, string senha,int rank, double t_inicio)
{
	// base case
	if (i == 0) // when len has been reached
	{
		if (senha.compare(s)==0) {
            cout << "Processo [" <<rank << "] encontrou a senha " << senha << endl;
            double t_fim = MPI_Wtime();
            cout << "Tempo de execução: " << t_fim - t_inicio << endl;
            MPI_Abort(MPI_COMM_WORLD,MPI_SUCCESS);
        }
		return;
	}

	// iterate through the array
	for (int j = 0; j < len; j++) {

		// Create new string with next character
		// Call generate again until string has
		// reached its len
		string appended = s + arr[j];
		generate(arr, i - 1, appended, len,senha,rank,t_inicio);
	}

	return;
}

// function to generate all possible passwords
void crack(char* arr, int k,int len, int rank,int nprocs,string senha,double t_inicio)
{
	// call for all required lengths
	//for (int i = 1; i <= len; i++) {
		//generate(arr, k, "", len,possibilidades,&(*posicao),inicio,fim);
        
	//}
    
    for (int i=rank;i<len;i=i+nprocs) {
        string primeiro_caractere(1,arr[i]);
        generate(arr, k-1, primeiro_caractere, len,senha,rank,t_inicio);
    }
    
}

string gen_random(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789";
    srand( (unsigned) time(NULL) * getpid());
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

int main()
{
	/*
    Caracteres disponíveis
    */
    char arr[] = {'1','2','3','4','5','6','7','8','9','0'};
	int len = sizeof(arr) / sizeof(arr[0]);
    /*
    Tamanho da senha
    */
    int k = 8;
	string minhaSenha;
    /*
    Análise de desempenho
    */
    double t_inicio;
    double t_fim;
    
    /*
    Iniciando MPI
    */
    MPI_Init(NULL,NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*
    Iniciando o tempo de execução, e envio da senha a ser procurada
    */
    int n = minhaSenha.length();
    char cMinhaSenha[n+1];
    t_inicio = MPI_Wtime();
    if (rank==0) {
        /*
        Gerando senha aleatória
        */
        minhaSenha = gen_random(8);
        /*
        Enviando senha a todos os processos
        */
        strcpy(cMinhaSenha,minhaSenha.c_str());
        MPI_Bcast(cMinhaSenha,k,MPI_CHAR,0,MPI_COMM_WORLD);
    }
    else {
        /*
        Recebendo senha
        */
        MPI_Bcast(cMinhaSenha,k,MPI_CHAR,0,MPI_COMM_WORLD);
        minhaSenha = "";
        for (int i=0;i<k;i++) {
            minhaSenha = minhaSenha + cMinhaSenha[i];
        }
    }
    
    /*
    Procurando senha
    */
    crack(arr, k,len,rank,nprocs,minhaSenha,t_inicio);
    
    /*
    Finalizando execução
    */
    MPI_Barrier(MPI_COMM_WORLD);
    t_fim = MPI_Wtime();
    if (rank==0) {
        cout << "Tempo de execução: " << t_fim - t_inicio << endl;
    }
    MPI_Finalize();
    return 0;
}
