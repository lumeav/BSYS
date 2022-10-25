#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <sys/time.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <time.h>


struct vector {
    int len;
    int *arr;
};
typedef struct vector vector;

void add(int d, vector *vec) {
    vec->arr = (int *) realloc(vec->arr, (vec->len + 1) * sizeof(int));
    vec->arr[vec->len] = d;
    vec->len += 1;
}

struct timespec timespec_diff(struct timespec *end, struct timespec *start) {
    struct timespec result; 
    result.tv_sec  = end->tv_sec  - start->tv_sec;
    result.tv_nsec = end->tv_nsec - start->tv_nsec;
    if (result.tv_nsec < 0) {
        --result.tv_sec;
        result.tv_nsec += 1000000000L;
    }
    return result;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Argument fehlt!\n");
        exit(1);
    }

    vector vec1;
    vec1.len = 0;
    vec1.arr = (int *) malloc(vec1.len * sizeof(int));

    int count = atoi(argv[1]);

    struct timespec loop_start, loop_end, loop_res;
    clock_gettime(CLOCK_MONOTONIC_RAW, &loop_start);
    for (int k = 0; k < count; k++)
    {
        add(k, &vec1);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &loop_end);
    loop_res = timespec_diff(&loop_end, &loop_start);

    long long int measure = loop_res.tv_sec * 1000000000L + loop_res.tv_nsec;

    for (int i = 0; i < vec1.len; i++) {
        printf("vec1[%d]: %d\n", i, vec1.arr[i]);
    }
    
    printf("Time: %Lf us\n", measure / 1000.0L);
    // printf("pInt: %p\n", (void *) pInt);
    // free(pInt);
    free(vec1.arr);
}