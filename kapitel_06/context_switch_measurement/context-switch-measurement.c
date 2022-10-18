#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <time.h>
#include <sched.h>

void bubblesort(long long int *array, int n) {
   int i, j, tmp;
   for (i = 1; i < n; i++) {
      for (j = 0; j < n - 1 ; j++) {
          if (array[j] > array[j + 1]) {
              tmp = array[j];
              array[j] = array[j + 1];
              array[j + 1] = tmp;
          }
      }
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

long double get_mean(long long int *array, long long int n) {
    long double mean = 0;
    long long int sum = 0;
    for (long long int k = 0; k < n; k++) {
        sum += array[k];
    }
    mean = sum / (long double) n;
    return mean;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Es muss genau ein Argument übergeben werden (cycles)");
    }
    long long int cycles = atoll(argv[1]);
    cpu_set_t set;
    CPU_ZERO(&set);
    int fd1[2];  // file descriptor 1
    int fd2[2];  // file descriptor 2
    char input_str[100];
    char output_str[100];
    struct timespec tv1 , tv2, tv_erg;
    long long int t = 0;
    long long int values[cycles];
    long double mean;
    int i;
    if (pipe(fd1) == -1) { // pipe fd1
        fprintf(stderr, "Pipe Failedd");
        return 1;
    }
    if (pipe(fd2) == -1) { // pipe fd2
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    int child_a = fork(); // fork a
    if (child_a < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (child_a == 0) { // child a
        CPU_SET(0, &set);
        sched_setaffinity(getpid(), sizeof(set), &set);
        for (i = 0; i < cycles; i++) {
            close(fd1[0]); // close read  
            clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
            write(fd1[1], &tv1, sizeof(tv1)); // write
            read(fd2[0], output_str, 100);
            close(fd2[1]);
            // close(fd1[1]);
            // close(fd2[0]);
        }
    } else { // parent
        int child_b = fork(); // fork b
        if (child_b < 0) { // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (child_b == 0) { // child b
            CPU_SET(0, &set);
            sched_setaffinity(getpid(), sizeof(set), &set);
            for (i = 0; i < cycles; i++) {
                read(fd1[0], &tv1, sizeof(tv1)); // read
                clock_gettime(CLOCK_MONOTONIC_RAW, &tv2); 
                tv_erg = timespec_diff(&tv2, &tv1);
                t = tv_erg.tv_sec * 1000000000L + tv_erg.tv_nsec;
                values[i] = t;
                close(fd1[1]); // close write
                close(fd2[0]);
                sprintf(input_str, "%s", "return");
                write(fd2[1], input_str, strlen(input_str) + 1);
                // close(fd1[0]);
                // close(fd2[1]);
            }
            bubblesort(values, cycles);
            long long int sub = cycles / 3;
            long long int *subset = malloc((cycles-sub)*sizeof(long long int));
            for(long long int l=0; l < cycles-sub; l++)
                subset[l] = values[l];

            for (long long int m = 0; m < cycles; m++) {
                printf("orig: %lld\n", values[m]);
            }
            for (long long int n = 0; n < cycles-sub; n++) {
                printf("sub: %lld\n", subset[n]);
            }
            mean = get_mean(subset, cycles - sub);
            printf("Mean: %.2Lfns\n", mean);
        } else { // parent
            waitpid(child_b, NULL, 0); // wait for child b
        }
    }
    return 0;
}