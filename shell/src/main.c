/* main.c - Ipiranga Shell

Copyright (c) 2018

This file is part of Ipiranga Shell.

Ipiranga Shell is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <posixeg/tparse.h>
#include <posixeg/debug.h>
#include <string.h>
#include <signal.h>


int main (int argc, char **argv)
{
    struct sigaction signal_handler;


    buffer_t *command_line;
    int i, j, aux, pid, status, fd;
    int **pipefds;
    pipeline_t *pipeline;

    fd = -1;
    command_line = new_command_line ();
    pipeline = new_pipeline ();


    memset(&signal_handler, 0, sizeof(struct sigaction));
    signal_handler.sa_handler = signalHandler;
    sigaction(SIGTSTP, &signal_handler, NULL); /* SIGTSTP is ^Z */
    sigaction(SIGINT, &signal_handler, NULL); /* SIGINT is ^C */

    while (1){

        printPrefix();
        fflush (stdout);
        aux = read_command_line (command_line);
        if (aux>=0&&!parse_command_line (command_line, pipeline)){

            /*Create pipes */
            if(pipeline->ncommands>1){
                pipefds = (int**)malloc(pipeline->ncommands*(sizeof(int*)));
                for(i=0;i<pipeline->ncommands;i++){
                    pipefds[i] = (int*)malloc(2*sizeof(int));
                }
                for (i=0; i<pipeline->ncommands-1; i++)
                pipe(pipefds[i]);

                i=0;
                while ( (i<pipeline->ncommands) && (pid=fork()) )
                i++;

                if (pid>0){
                    for (j=0; j<pipeline->ncommands-1; j++)
                    {
                        close (pipefds[j][0]);
                        close (pipefds[j][1]);
                    }
                    waitpid (pid, &status, 0);
                }

                if (pid==0){
                    if(i==0){
                        close (pipefds[i][0]);
                        close (1);
                        dup(pipefds[i][1]);
                        close (pipefds[i][1]);
                        for(j=1; j<pipeline->ncommands-1; j++){
                            close (pipefds[j][0]);
                            close (pipefds[j][1]);
                        }
                    }

                    else if(i==pipeline->ncommands-1){
                        close (pipefds[i-1][1]);
                        close (0);
                        dup(pipefds[i-1][0]);
                        close (pipefds[i-1][0]);
                        for(j=0; j<pipeline->ncommands-2; j++){
                            close (pipefds[j][0]);
                            close (pipefds[j][1]);
                        }
                    }else{
                        close (0);
                        dup(pipefds[i-1][0]);
                        close (1);
                        dup(pipefds[i][1]);
                        for(j=0; j<pipeline->ncommands-1; j++){
                            close (pipefds[j][0]);
                            close (pipefds[j][1]);
                        }
                    }
                    if(builtinCommand(pipeline->command[i])){
                        exit(1);
                    }else{
                        if(execvp(pipeline->command[i][0], pipeline->command[i])<0){
                            printf("\033[1;31m[ERROR]:\033[0m command not found: %s\n",pipeline->command[i][0]);
                            exit(1);
                        }
                    }
                }
            }else{
                if(!builtinCommand(pipeline->command[0])){
                    pid = fork();
                    if(pid==0){
                        if ( REDIRECT_STDIN(pipeline)){
                            close(0);
                            fd = open (pipeline->file_in, O_RDONLY,  S_IRUSR | S_IWUSR);
                        }
                        if ( REDIRECT_STDOUT(pipeline)){
                            close(1);
                            fd = open (pipeline->file_out, O_CREAT | O_TRUNC | O_RDWR,  S_IRUSR | S_IWUSR);
                        }
                        if(execvp(pipeline->command[0][0], pipeline->command[0])<0){
                            printf("\033[1;31m[ERROR]:\033[0m command not found: %s\n",pipeline->command[0][0]);
                            exit(1);
                        }
                    }else{
                        wait(&status);
                    }
                }
            }
        }
    }

    close(fd);
    release_command_line (command_line);
    release_pipeline (pipeline);

    return EXIT_SUCCESS;
}
