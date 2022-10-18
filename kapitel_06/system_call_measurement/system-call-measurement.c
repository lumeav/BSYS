#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <sys/time.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <time.h>


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
        fprintf(stderr, "Anzahl Schleifendurchläufe muss mit übergeben werden!\n");
    }

    struct timespec t_syscall_start , t_syscall_end, t_syscall_result, t_loop_start, t_loop_end, t_loop_result;
    long long int cycles = atoll(argv[1]);
    long long int i, t_loop_ns, t_syscall_ns;

    clock_gettime(CLOCK_MONOTONIC_RAW, &t_loop_start);
    for (i = 0; i < cycles; i++) {

    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_loop_end);
    t_loop_result = timespec_diff(&t_loop_end, &t_loop_start);
    t_loop_ns = t_loop_result.tv_sec * 1000000000L + t_loop_result.tv_nsec;

    printf("loop: %lldns\n", t_loop_ns / cycles);

    i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_syscall_start);
    for (i = 0; i < cycles; i++) {
        // read(0, NULL, 0);
        getpid();
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &t_syscall_end);
    t_syscall_result = timespec_diff(&t_syscall_end, &t_syscall_start);
    t_syscall_ns = t_syscall_result.tv_sec * 1000000000L + t_syscall_result.tv_nsec;

    printf("syscall with loop: %lldns\n", t_syscall_ns  / cycles);

    long long int res_ns = (t_syscall_ns - t_loop_ns) / cycles; 
    printf("System call: %lld ns\n", res_ns);
    return 0;
}

