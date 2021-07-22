#include <stdio.h>
#include <stdlib.h>

int main() {

    int *vetor = malloc(4 * sizeof(int));
    vetor[0] = 10;
    vetor[1] = 22;
    vetor[2] = 36;
    vetor[3] = 41;

    int *pt;
    pt = &vetor[1];

    printf("%d\n",pt[0]);
    printf("%ld\n",(long int)(6.8));
    return 0;
}
