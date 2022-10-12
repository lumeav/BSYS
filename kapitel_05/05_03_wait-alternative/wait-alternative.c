#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/wait.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <string.h>
// #include <fcntl.h>
// #include <time.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) {
        fprintf(stderr, "pipe failed\n");
    }
    char str[50] = "wait";
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello\n");
        write(fd[1], str, strlen(str) + 1);
    } else { // parent goes down this path (main)
        read(fd[0], str, strlen(str) + 1);
        printf("goodbye\n");
    }
    return 0;
}