#include <bits/stdc++.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <mpi.h>
#include <fstream>

using namespace std;


void adicionarPossibilidade(string *possibilidades, long int *posicao, string valor) {
    possibilidades[*posicao] = valor;
    *posicao = *posicao + 1;
}

// Recursive helper function, adds/removes characters
// until len is reached
void generate(char* arr, int i, string s, int len, string *possibilidades, long int *posicao, string senha)
{
	// base case
	if (i == 0) // when len has been reached
	{
		// print it out
		//cout << s << "\n";
		if (senha.compare(s)==0) {
            cout << "Encontrei" << endl;
            return;
        }
        //adicionarPossibilidade(possibilidades,&(*posicao),s);
        // cnt++;

		return;
	}

	// iterate through the array
	for (int j = 0; j < len; j++) {

		// Create new string with next character
		// Call generate again until string has
		// reached its len
		string appended = s + arr[j];
		generate(arr, i - 1, appended, len,possibilidades,&(*posicao),senha);
	}

	return;
}

// function to generate all possible passwords
void crack(char* arr, int k,int len,string *possibilidades, long int *posicao,int primeiro, int ultimo,string senha)
{
	// call for all required lengths
	//for (int i = 1; i <= len; i++) {
		//generate(arr, k, "", len,possibilidades,&(*posicao),inicio,fim);
        
	//}
    
    for (int i=primeiro;i<ultimo;i++) {
        string primeiro_caractere(1,arr[i]);
        //cout << i << endl;
        generate(arr, k-1, primeiro_caractere, len,possibilidades,&(*posicao),senha);
    }
    
}

void forca_bruta(string *possibilidades, long int tamanho,string senha) {
    long int i;
    for (i=0;i<tamanho;i++) {
        if (senha.compare(possibilidades[i])==0) {
            cout << "Encontrei!: " << i << endl;
        }
    }
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
	
    MPI_Init(NULL,NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double t_inicio;
    double t_fim;
    /*
    Possibilidades
    */
    long int total_possibilidades = (long int)pow(sizeof(arr),k);
    string minhaSenha = "94212303";
    string *possibilidades = NULL;
    long int posicao = 0;
    long int subtotal;
    subtotal = (long int)(total_possibilidades/nprocs);
    t_inicio = MPI_Wtime();
    if (rank==0) {
        possibilidades = new string[subtotal];
        int inicio = 0;
        int fim = (int)(len/nprocs);
        cout << inicio << "-" << fim << endl;
        crack(arr, k,len,possibilidades,&posicao,inicio,fim,minhaSenha);
        //crack(arr, k,len,possibilidades,&posicao,2,5);
        //forca_bruta(possibilidades,subtotal,minhaSenha);
        cout << "Rank " << rank << " terminou..." << endl;
    }
    else if (rank==1) {
        possibilidades = new string[subtotal];
        int inicio = (int)(len/nprocs);
        int fim = len;
        cout << inicio << "-" << fim << endl;
        crack(arr, k,len,possibilidades,&posicao,inicio,fim,minhaSenha);
        //crack(arr, k,len,possibilidades,&posicao,8,10);
        //forca_bruta(possibilidades,subtotal,minhaSenha);
        cout << "Rank " << rank << " terminou..." << endl;
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    t_fim = MPI_Wtime();
    if (rank==0) {
        cout << "Tempo de execução: " << t_fim - t_inicio << endl;
    }
    MPI_Finalize();
    delete[] possibilidades;
    return 0;
}
