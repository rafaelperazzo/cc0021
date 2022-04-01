#include <stdio.h>
#include <omp.h>

int fib(int n);

int main() {

    printf("%d\n",fib(20));
    return 0;
}

int fib(int n) {

    int x,y;
    if (n<2) return n;

    #pragma omp task shared(x) 
    {
        x = fib(n-1);
    }
        
    #pragma omp task shared(y)
    {
        y = fib(n-2);
    }
        
    #pragma omp taskwait
    
    return (x+y);

}