#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

    const long long iternum=2000000000;
    long long sum=0;
    double x,y,pi;
    long long i;
    clock_t inicio = clock();
    srand((unsigned)time(0));
    for(long long i=0;i<iternum;++i){
        x=(double)rand()/RAND_MAX;
        y=(double)rand()/RAND_MAX;
        if(x*x+y*y<1) 
            ++sum;
    }

    pi=(4.0*sum)/(double)iternum;
    clock_t fim = clock();
    printf("Elapsed: %f seconds\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Aproximacao de pi: %f\n",pi);
    return 0;
}