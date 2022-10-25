#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *pInt = (int *) malloc(100 * sizeof(int));
    pInt[99] = 5;
    free(pInt);
    printf("pInt[99]: %d\n", pInt[99]);
}