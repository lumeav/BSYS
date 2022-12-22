#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "mythreads.h"

int loops = 1;
int threads = 1;

typedef struct node_t {
    int value;
    struct node_t *next;
    pthread_mutex_t lock;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t listLock;
} list_t;

typedef struct __thread_arguments {
    int numberLoops;
    list_t* list;
    int threadID;
} thread_arguments;

void list_init(list_t *l) {
    // Dummy Knoten wird hinzugefuegt, damit beim Einfuegen des ersten Knotens 
    // head != NULL ist. Ansonsten koennte eine Race Condition auftreten
    node_t *new = Malloc(sizeof(node_t));
    Mutex_init(&new->lock);
    new->next = NULL;
    new->value = 0;
    l->head = new;
}

void list_insert(list_t *l, int key) {
    node_t *new = Malloc(sizeof(node_t));
    new->value = key;
    Mutex_init(&new->lock);

    Mutex_lock(&l->listLock);

    new->next = l->head;
    l->head = new;

    Mutex_unlock(&l->listLock);

}

int list_lookup(list_t *l, int key) {
    int rv = -1;
    node_t *curr = l->head;
    Mutex_lock(&curr->lock);
    while (curr) {
        if (curr->value == key) {
            Mutex_unlock(&curr->lock);
            rv = 0;
            break;
        }
        Mutex_lock(&curr->next->lock);
        Mutex_unlock(&curr->lock);
        //Only release lock after acquiring the lock of the next node, preventing overtaking
        curr = curr->next;
    }
    return rv; // failure and success
}

void* thread(void* arguments) {
    thread_arguments* args = (thread_arguments *) arguments;
    for (int i = 1; i <= args->numberLoops; i++) {
        list_insert(args->list, args->threadID * args->numberLoops + i);
    }
    for (int i = 1; i <= args->numberLoops; i++) {
        list_lookup(args->list, args->threadID * args->numberLoops + i);
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
    
    thread_arguments args[threads];

    list_t *l = Malloc(sizeof(list_t));
    list_init(l);

    for (int i = 0; i < threads; i++) {
        args[i].numberLoops = loops;
        args[i].list = l;
        args[i].threadID = i;
    }

    pthread_t allThreads[threads];

    struct timespec start, end;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
		perror("clock gettime");
		exit(1);
	}
    for (int i = 0; i < threads; i++) {
		Pthread_create(&allThreads[i], NULL, thread, &args[i]);
	}

    for (int i = 0; i < threads; i++) {
        Pthread_join(allThreads[i], NULL);
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
