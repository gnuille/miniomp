#include <stdio.h>
#include <stdlib.h>

long result=0;

void foo() {
    {
    int argum = 1;
    {
    for (long i = 0; i < 10; i++) {
        result += argum;
        }

    argum++;
    for (long i = 0; i < 10; i++) {
        result += argum;
        }

    argum = result;
    for (long i = 0; i < 10; i++) {
        result += argum;
        }
    }

    printf("Hello from third task, up to now result=%ld and argum = %d\n", result, argum);
    }
}

int main(int argc, char *argv[]) {
    foo();
    printf("Back in main ... result = %ld\n", result);
}
