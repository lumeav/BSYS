#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int i = 5;
	int *pInt = &i;
    /* int *pInt = (int *) malloc(sizeof(int)); */
    pInt = NULL;
    printf("pInt: %i\n", *pInt);
}
