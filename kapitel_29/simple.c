//#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "mythreads.h"

int counter = 0;
int loops = 1;
int threads = 1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment() {
	for(int i = 0; i < loops; i++) {
		Mutex_lock(&lock);
		counter++;
		Mutex_unlock(&lock);
	}
    return NULL;
}

int main(int argc, char *argv[]) {

    int option;

    while ((option = getopt(argc, argv, "ht:l:")) != -1) {
        switch (option)
        {
            case 'h':;
                printf("-l number of loops, default 1\n");
                printf("-t number of threads, default 1\n");
                exit(0);
            case 't':
                threads = atoi(optarg);
                break;
            case 'l':
                loops = atoi(optarg);
                break;
            default:
                printf("Invalid arguments!\n");
                exit(1);
        }
    }
	
    //cpu_set_t  mask;
    //CPU_ZERO(&mask);
    //CPU_SET(4, &mask);
    //sched_setaffinity(0, sizeof(mask), &mask); 
	//test with different numbers of cpus: lscpu or cat /proc/cpuinfo  
	
	pthread_t thread[threads];
	struct timespec start, end;
	if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
		perror("clock gettime");
		exit(1);
	}
	for(int i = 0; i < threads; i++) {
		Pthread_create(&thread[i], NULL, increment, NULL);
	}
	for(int i = 0; i < loops; i++) {
		Mutex_lock(&lock);
		counter++;
		Mutex_unlock(&lock);
	}
	for(int i = 0; i < threads; i++) {
		Pthread_join(thread[i], NULL);
	}
	if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
		perror("clock gettime");
		exit(1);
	}
	double time = ((end.tv_sec - start.tv_sec) * 1000000000.0)
                + end.tv_nsec - start.tv_nsec;
	printf("%f ", time);
	return 0;
}
