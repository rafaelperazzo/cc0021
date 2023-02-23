#include <stdio.h>
#include <omp.h>

int main () {
	#pragma omp parallel num_threads(4)
	{
		printf("Ola mundo2!\n");
	}
}
