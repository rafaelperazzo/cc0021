// C program to print all permutations with repetition
// of characters
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void adicionarSenha(char **senhas, long int *posicao, char valor[]) {
    //senhas[*posicao] = valor;
    strcpy(senhas[*posicao],valor);
	*posicao = *posicao + 1;
}

/* Following function is used by the library qsort() function
to sort an array of chars */
int compare (const void * a, const void * b);

/* The main function that recursively prints all repeated
permutations of the given string. It uses data[] to store all
permutations one by one */
void allLexicographicRecur (char *str, char* data, int last, int index,char **possibilidades,long int *posicao)
{
    int i, len = strlen(str);
	// One by one fix all characters at the given index and recur for
	// the/ subsequent indexes
	for ( i=0; i<len; i++ )
	{
		// Fix the ith character at index and if this is not the last
		// index then recursively call for higher indexes
		data[index] = str[i] ;

		// If this is the last index then print the string stored in
		// data[]
		if (index == last) {
            printf("%s\n", data);
            adicionarSenha(possibilidades,&(*posicao),data);
        }
		else // Recur for higher indexes
			allLexicographicRecur (str, data, last, index+1,possibilidades,&(*posicao));
	}
}

/* This function sorts input string, allocate memory for data (needed
for allLexicographicRecur()) and calls allLexicographicRecur() for
printing all permutations */
void allLexicographic(char *str,char **possibilidades,long int *posicao)
{
	int len = strlen (str) ;
	// Create a temp array that will be used by allLexicographicRecur()
	char *data = (char *) malloc (sizeof(char) * (len + 1)) ;
	data[len] = '\0';

	// Sort the input string so that we get all output strings in
	// lexicographically sorted order
	qsort(str, len, sizeof(char), compare);

	// Now print all permutaions
	allLexicographicRecur (str, data, len-1, 0,possibilidades,&(*posicao));

	// Free data to avoid memory leak
	free(data);
}

// Needed for library function qsort()
int compare (const void * a, const void * b)
{
	return ( *(char *)a - *(char *)b );
}

// Driver program to test above functions
int main()
{
	char str[] = "ABCD";
    int r = sizeof(str)-1;
    int k = 4;
	printf("Total de caracteres: %d\n",r);
	
    //TOTAL DE POSSIBILIDADES
	long int total;
	total = (int)pow(r,k);
	printf("Total: %ld\n",total);
	
	//ALOCANDO MATRIZ DE POSSIBILIDADES
	char **possibilidades = (char **)malloc(total * sizeof(char*));
	for (int i=0; i<total;i++) {
		possibilidades[i] = (char *)malloc(r*sizeof(char));
	}
    
    long int posicao = 0;
    
	//GERANDO TODAS AS POSSIBILIDADES
    allLexicographic(str,possibilidades,&posicao);
    
	return 0;
}
