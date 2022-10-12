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
        // char *myargs[] = {
        //     strdup("ls"),
        //     NULL
        //     };
        char *myenv[] =  {
            "SHELL=/bin/bash",
            "LOGNAME=a_username",
            "OSTYPE=L1NuX",
            NULL
            };
        execl("/bin/ls", "ls", NULL);
        // execle("/bin/ls", "ls", NULL, myenv);
        // execlp("ls", "ls", NULL);
        // execv("/bin/ls", myargs);
        // execvp("ls", myargs);
        // execvpe("ls", myargs, myenv);
    } else { // parent goes down this path (main)
        // int rc_wait = wait(NULL);
    }
    return 0;
}
