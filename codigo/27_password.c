// C++ program to generate all passwords for given characters
#include <stdio.h>

// int cnt;

// Recursive helper function, adds/removes characters
// until len is reached
void generate(char* arr, int i, string s, int len)
{
	// base case
	if (i == 0) // when len has been reached
	{
		// print it out
		cout << s << "\n";
		// cnt++;
		return;
	}

	// iterate through the array
	for (int j = 0; j < len; j++) {

		// Create new string with next character
		// Call generate again until string has
		// reached its len
		string appended = s + arr[j];
		generate(arr, i - 1, appended, len);
	}

	return;
}

// function to generate all possible passwords
void crack(char* arr, int len)
{
	// call for all required lengths
	for (int i = 1; i <= len; i++) {
		generate(arr, i, "", len);
	}
}

// driver function
int main()
{
	char arr[] = { 'a', 'b', 'c' };
	int len = sizeof(arr) / sizeof(arr[0]);
	crack(arr, len);

	//cout << cnt << endl;
	return 0;
}
