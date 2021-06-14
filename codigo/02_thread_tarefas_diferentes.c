#include <stdio.h>
#include <omp.h>

//TAREFA 1
void tarefa1(int n) {
	int i;
	for (i=0;i<n;i++) {
		printf("(%d) - %d\n",omp_get_thread_num(),i);
	}
}
//TAREFA 2
void tarefa2(int a, int b) {
	printf("(%d) - %d\n",omp_get_thread_num(),a+b);
}	

int main () {
	#pragma omp parallel
	{
		#pragma omp sections 
		{
			#pragma omp section 
				tarefa1(10); 
			#pragma omp section
				tarefa2(20,30);
		}	
	}
}

