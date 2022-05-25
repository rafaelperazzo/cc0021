#include <stdio.h>

int main() {

    int i;
    float a = 1.0987;
    float b = 2.02302;
    float c = 0;
    for (i=0;i<1000000000;i++) {
        if (1==1) {
            c = a/b;
        }
    }

    return 0;
}