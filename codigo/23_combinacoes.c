//Fonte: https://www.geeksforgeeks.org/combinations-with-repetitions/
// C program to print all combination of size r in an array
// of size n with repetitions allowed
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 4

long int fatorial(int n) {

	long int prod = 1;
	for (int i=1; i<=n;i++) {
		prod = prod*i;
	}
	return (prod);
}

void mostrarMatriz(char **p) {
	printf("%s\n",p[0]);
	printf("%s\n",p[1]);
}

void adicionarSenha(char **senhas, long int *posicao, char valor[]) {
	senhas[*posicao] = valor;
	*posicao = *posicao + 1;
}

/* arr[] ---> Input Array
chosen[] ---> Temporary array to store indices of
				current combination
start & end ---> Starting and Ending indexes in arr[]
r ---> Size of a combination to be printed */
void CombinationRepetitionUtil(int chosen[], char arr[],
					int index, int r, int start, int end, char **possibilidades)
{
	// Since index has become r, current combination is
	// ready to be printed, print
	if (index == r)
	{
		char senha[r];
		for (int i = 0; i < r; i++) {
			printf("%c ", arr[chosen[i]]);
			senha[i] = arr[chosen[i]];
		}

		printf("\n");
		return;
	}

	// One by one choose all elements (without considering
	// the fact whether element is already chosen or not)
	// and recur
	for (int i = start; i <= end; i++)
	{
		chosen[index] = i;
		CombinationRepetitionUtil(chosen, arr, index + 1,
											r, i, end,possibilidades);
	}
	return;
}

// The main function that prints all combinations of size r
// in arr[] of size n with repetitions. This function mainly
// uses CombinationRepetitionUtil()
void CombinationRepetition(char arr[], int n, int r,char **possibiliades)
{
	// Allocate memory
	int chosen[r+1];

	// Call the recursive function
	CombinationRepetitionUtil(chosen, arr, 0, r, 0, n-1,possibiliades);
}

// Driver program to test above functions
int main()
{
	//CARACTERES DISPONIVEIS E TAMANHO DE CADA COMBINACAO
	char arr[] = {'1','2','3','4'};
	int n = sizeof(arr)/sizeof(arr[0]);
	int r = 4;
	
	//TOTAL DE POSSIBILIDADES
	long int total;
	total = fatorial(n+r-1)/((double)(fatorial(r)*fatorial(n-1)));
	printf("Total: %ld\n",total);
	
	//ALOCANDO MATRIZ DE POSSIBILIDADES
	char **possibilidades = (char **)malloc(total * sizeof(char*));
	for (int i=0; i<total;i++) {
		possibilidades[i] = (char *)malloc(r*sizeof(char));
	}

	CombinationRepetition(arr, n, r,possibilidades);

	return 0;
}
