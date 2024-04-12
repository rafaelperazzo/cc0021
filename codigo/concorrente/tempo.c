#include <stdio.h>
#include <sys/time.h>
#include<unistd.h>

int main () {
    
    // Start measuring time
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    sleep(4);
    
    // Stop measuring time and calculate the elapsed time
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    
    printf("Time measured: %.3f seconds.\n", elapsed);
    
    return 0;
}