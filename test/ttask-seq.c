#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

long result=0;

void foo() {
//#pragma omp single
    {
    printf("All threads created\n");
    int argum = 1;
    for (long i = 0; i < 10; i++) {
        result += argum;
        }

    for (long i = 0; i < 10; i++) {
        argum++;
        result += argum;
        }

    printf("Hello from third task, up to now result=%ld and argum = %d\n", result, argum);
    }
}

int main(int argc, char *argv[]) {
    foo();
    printf("Back in main ... result = %ld\n", result);
}
