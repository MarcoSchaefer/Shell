#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


/*Returns 1 if the command received is a builtin command. Returns 0 if isn't*/
int builtinCommand(char** command){
    list_node_t *job_it;
    job* job_cast;
    int result,i,index,pid;
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
    if(strcmp(command[0],"fg")==0){
        if(job_list->size<1){
            printf("\033[1;31m[ERROR]:\033[0m no current job\n");
            return 1;
        }
        if(!command[1]){
            job_it = job_list->first;
            job_cast = (job*)job_it->value;
            pid = job_cast->pid;
            kill(pid,SIGCONT);
            setpgid(pid, shell_group);
            printf("{%d}",getpgid(pid));
            waitpid (pid, NULL, 0);
        }else{
            index = atoi(command[1]);
            if(index>0){
                job_it = job_list->first;
                i=0;
                while (job_it)
                  {
                    i++;
                    if(i==index){
                        job_cast = (job*)job_it->value;
                        pid = job_cast->pid;
                        kill(pid,SIGCONT);
                        setpgid(pid, shell_group);
                        printf("{%d}",getpgid(pid));
                        waitpid (pid, NULL, 0);
                        break;
                    }
                    job_it = job_it->next;
                  }
            }
        }
        return 1;
    }

    if(strcmp(command[0],"bg")==0){
        if(job_list->size<1){
            printf("\033[1;31m[ERROR]:\033[0m no current job\n");
            return 1;
        }
        if(!command[1]){
            job_it = job_list->first;
            job_cast = (job*)job_it->value;
            pid = job_cast->pid;
            setpgid(pid, pid);
            printf("{%d %d}",errno,getpgid(pid));
            kill(pid,SIGCONT);
        }else{
            index = atoi(command[1]);
            if(index>0){
                job_it = job_list->first;
                i=0;
                while (job_it)
                  {
                    i++;
                    if(i==index){
                        job_cast = (job*)job_it->value;
                        pid = job_cast->pid;
                        setpgid(pid, pid);
                        printf("{%d}",getpgid(pid));
                        kill(pid,SIGCONT);
                        break;
                    }
                    job_it = job_it->next;
                  }
            }
        }
        return 1;
    }
    return 0;
}
