//Fonte: https://www.geeksforgeeks.org/combinations-with-repetitions/
// C program to print all combination of size r in an array
// of size n with repetitions allowed
#include <stdio.h>

/* arr[] ---> Input Array
chosen[] ---> Temporary array to store indices of
				current combination
start & end ---> Starting and Ending indexes in arr[]
r ---> Size of a combination to be printed */
void CombinationRepetitionUtil(int chosen[], int arr[],
					int index, int r, int start, int end)
{
	// Since index has become r, current combination is
	// ready to be printed, print
	if (index == r)
	{
		for (int i = 0; i < r; i++)
			printf("%d ", arr[chosen[i]]);
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
											r, i, end);
	}
	return;
}

// The main function that prints all combinations of size r
// in arr[] of size n with repetitions. This function mainly
// uses CombinationRepetitionUtil()
void CombinationRepetition(int arr[], int n, int r)
{
	// Allocate memory
	int chosen[r+1];

	// Call the recursive function
	CombinationRepetitionUtil(chosen, arr, 0, r, 0, n-1);
}

// Driver program to test above functions
int main()
{
	int arr[] = {1, 2, 3, 4,5,6,7,8};
	int n = sizeof(arr)/sizeof(arr[0]);
	int r = 4;
	CombinationRepetition(arr, n, r);
	return 0;
}
