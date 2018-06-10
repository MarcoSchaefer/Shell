#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int signal){
    switch (signal) {
        case SIGINT:
            printf("\n");
            break;
        case SIGTSTP:
            printf("\n");
            break;
    }
}
