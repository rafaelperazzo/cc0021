#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

    const long long iternum=1000000000;
    long long sum=0;
    double x,y,pi;
    long long i;

    srand((unsigned)time(0));
    for(long long i=0;i<iternum;++i){
        x=(double)rand()/RAND_MAX;
        y=(double)rand()/RAND_MAX;
        if(x*x+y*y<1) 
            ++sum;
    }

    pi=(4.0*sum)/(double)iternum;
    printf("Aproximacao de pi: %f\n",pi);
    return 0;
}