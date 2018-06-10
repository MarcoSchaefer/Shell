#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*Returns 1 if the command received is a builtin command. Returns 0 if isn't*/
int builtinCommand(char** command){
    list_node_t *job_it;
    job* job_cast;
    int result,i;
    if(strcmp(command[0],"cd")==0){
        result = chdir(command[1]);
        if(result<0){
            printf("\033[1;31m[ERROR]:\033[0m directory not found: %s\n",command[1]);
        }
        return 1;
    }
    if(strcmp(command[0],"exit")==0){
        exit(0);
    }
    if(strcmp(command[0],"jobs")==0){
        printf ("Total jobs: %d\n", job_list->size);
        if(job_list->size<=0){
            return 1;
        }
        job_it = job_list->first;
        i=0;
        while (job_it)
          {
            i++;
            job_cast = (job*)job_it->value;
            printf ("[%d] PID:%d Command:%s\n",i,job_cast->pid,job_cast->command);
            job_it = job_it->next;
          }
        return 1;
    }
    return 0;
}
