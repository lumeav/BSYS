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


typedef struct node {
    int val;
    struct node * next;
} node_t;

void push(node_t * head, int val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* jetzt koennen wir eine neue Variable hinzufuegen */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
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

    node_t *head = NULL;
    head = malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }
    head->val = 1;
    head->next = NULL;

    int count = atoi(argv[1]);

    struct timespec loop_start, loop_end, loop_res;
    clock_gettime(CLOCK_MONOTONIC_RAW, &loop_start);
    for (int k = 0; k < count; k++)
    {
        push(head, k);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &loop_end);

    loop_res = timespec_diff(&loop_end, &loop_start);

    long long int measure = loop_res.tv_sec * 1000000000L + loop_res.tv_nsec;

    print_list(head);

    printf("Time: %Lf us\n", measure / 1000.0L);

}