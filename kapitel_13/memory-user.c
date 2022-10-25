#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

int main(int argc, char * argv[]) {

    
    if (argc != 3) {
        printf("Please specify the amount of memory allocated (in mb) along with the run time");
        exit(0);
    }
    int mem = atoi(argv[1]) * 1024 * 1024;
    int time = atoi(argv[2]);

    int *array = malloc(mem);

    struct timeval present_time;
    time_t start,end;
    gettimeofday(&present_time, NULL);
    start = present_time.tv_sec;
    end = start + time;
    

    while (start < end) {

        for(int i = 0; i < mem / sizeof(int); i++) {
            array[i] = 0;
        }
        gettimeofday(&present_time, NULL);
        start = present_time.tv_sec;
        
    }
    free(array);
    exit(0);
}