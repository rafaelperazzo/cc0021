#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int soma = 0;
    #pragma omp parallel for lastprivate(soma) num_threads(2) 
    
        for (i=0;i<100000;i++) {
            soma = soma + i;
        }
        printf("%d\n",soma);
    
    
   
    return 0;
}