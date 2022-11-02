#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *pInt = (int *) malloc(100 * sizeof(int));
    pInt[100] = 0;
    printf("pInt: %p\n", (void *) pInt);
    free(pInt);
}
