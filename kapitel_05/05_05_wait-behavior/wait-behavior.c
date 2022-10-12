#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <time.h>

int main(void) {
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        int rc_wait = wait(NULL);
        printf("hello, I am child (rc_wait:%d) (pid:%d)\n", rc_wait, (int) getpid());
        /* printf("hello, I am child (pid:%d)\n", (int) getpid()); */
    } else { // parent goes down this path (main)
        /* int rc_wait = wait(NULL); */
        /* printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid()); */
        printf("hello, I am parent of %d  (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}
