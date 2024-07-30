#include <stdio.h>
#include <omp.h>

int main () {
	
	#pragma omp parallel num_threads(4)
	{
		int i;
		#pragma omp for
			for (i=0; i<=10; i++) {
				printf("Thread %d executa iteracao %d do for\n",omp_get_thread_num(),i);
			}
	}
}