#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *pInt = (int *) malloc(100 * sizeof(int));
    pInt[99] = 0;
    printf("pInt: %p\n", (void *) pInt);
    // free(pInt);
    free(&pInt[1]);
}