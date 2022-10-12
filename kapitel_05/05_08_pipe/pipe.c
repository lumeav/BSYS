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
    int fd[2];  // file descriptor
    if (pipe(fd) == -1) { // pipe fd
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    char str[100];
    int child_a = fork(); // fork a
    if (child_a < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (child_a == 0) { // child a
        // close(fd[1]);
        dup2(fd[0], 0);
        scanf("%s", str);
        printf("%s\n", str);
    } else { // parent
        // waitpid(child_a, NULL, 0); // wait for child a
        int child_b = fork(); // fork b
        if (child_b < 0) { // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (child_b == 0) { // child b
            // close(fd[0]);
            dup2(fd[1], 1);
            printf("Naaaaaachricht!\n");
        } else { // parent
            waitpid(child_b, NULL, 0); // wait for child b
        }
    }
    return 0;
}