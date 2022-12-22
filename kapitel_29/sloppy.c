#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "mythreads.h"

#define MAXTHREADS 200
#define NUMCPUS 4

int threads = 1;
int loops = 1;
int tresholds = 1;

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    // Da erst zur Laufzeit bekannt ist, wie viele Threads erstellt werden
    // sollen, wird genuegend Speicherplatz reserviert
    int local[MAXTHREADS];
    pthread_mutex_t llock[MAXTHREADS];
    int treshold;
} counter_t;

void init(counter_t *c, int treshold) {
    c->treshold = treshold;
    c->global = 0;
    Mutex_init(&c->glock);
    for(int i = 0; i < threads; i++) {
        c->local[i] = 0;
        Mutex_init(&c->llock[i]);
    }
}

void update(counter_t *c, int threadID) {
    int cpu = threadID % NUMCPUS;
    Mutex_lock(&c->llock[cpu]);
    c->local[cpu]++;
    if(c->local[cpu] >= c->treshold) {
        Mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    Mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
    Mutex_lock(&c->glock);
    int val = c->global;
    Mutex_unlock(&c->glock);
    return val;
}

typedef struct __update_arguments {
    counter_t *counter;
} update_arguments;

void* increment(void* updateArguments) {
    update_arguments *updateArgument = (update_arguments*) updateArguments;
    int threadID = pthread_self();
    for(int i = 0; i < loops; i++) {
        update(updateArgument->counter, threadID);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    int option;

    while ((option = getopt(argc, argv, "ht:l:n:")) != -1) {
        switch (option)
        {
            case 'h':;
                printf("-l number of loops, default 1\n");
                printf("-t number of threads, default 1\n");
                printf("-n size of tresholds, default 1\n");
                exit(0);
            case 't':
                threads = atoi(optarg);
                if (threads > MAXTHREADS) {
                    printf("Number of threads should not exceed %d\n", MAXTHREADS);
                    exit(1);
                }
                break;
            case 'l':
                loops = atoi(optarg);
                break;
            case 'n':
                tresholds = atoi(optarg);
                break;
            default:
                printf("Invalid arguments!\n");
                exit(1);
        }
    }
    
    pthread_t thread[threads];
    struct timespec start, end;
    counter_t counter;
    
    init(&counter, tresholds);
    
    update_arguments updateArguments[threads];
    
    for(int i = 0; i < threads; i++) {
        updateArguments[i].counter = &counter;
    }
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
		perror("clock gettime");
		exit(1);
	}
	for(int i = 0; i < threads; i++) {
		Pthread_create(&thread[i], NULL, increment, &updateArguments[i]);
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

