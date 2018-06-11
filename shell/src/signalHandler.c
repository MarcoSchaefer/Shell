#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signalHandler(int signal){
    pid_t pid;
    switch (signal) {
        case SIGINT:
            printf("\n");
            break;
        case SIGTSTP:
            printf("\n");
            addJob(pipeline);
            break;
        case SIGCHLD:
            while ((pid = waitpid(-1, NULL, WNOHANG)) != -1)
            {
                printf("\n [%d] Terminated \n",pid);
            }
            break;
    }
}
