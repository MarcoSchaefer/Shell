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


/* void test(void); */

int go_on = 1;			/* This variable controls the main loop. */

int main (int argc, char **argv)
{
  buffer_t *command_line;
  int i, j, aux, pid, status, fd;
  int **pipefds;
  pipeline_t *pipeline;

  fd = -1;
  command_line = new_command_line ();
  pipeline = new_pipeline ();

  /* This is the main loop. */
  while (go_on){

      printPrefix();
      fflush (stdout);
      aux = read_command_line (command_line);
      sysfatal (aux<0);

      /* Parse command line (see tparse.*) */

      if (!parse_command_line (command_line, pipeline)){
    	  /*printf ("  Pipeline has %d command(s)\n", pipeline->ncommands);*/

    	  for (i=0; pipeline->command[i][0]; i++)
    	    {
    	      /*printf ("  Command %d has %d argument(s): ", i, pipeline->narguments[i]);*/
    	      for (j=0; pipeline->command[i][j]; j++){
    		      /*printf ("%s ", pipeline->command[i][j]);*/
            }
    	      /*printf ("\n");*/
    	    }


    	  if ( RUN_FOREGROUND(pipeline)){
          /*printf ("  Run pipeline in foreground\n");*/
        }else{
          /*printf ("  Run pipeline in background\n")*/;
        }

        /*Create pipes */
        if(pipeline->ncommands>1){
          pipefds = (int**)malloc(pipeline->ncommands*(sizeof(int*)));
          for(i=0;i<pipeline->ncommands;i++){
            pipefds[i] = (int*)malloc(2*sizeof(int));
          }
          /* Create N-1 pipes. */
            for (i=0; i<pipeline->ncommands-1; i++)
              pipe(pipefds[i]);


            /* Fork N processes. Note that, only the parent iterates through the loop,
               while childs immediately leave the loop and procedd.*/

            i=0;
            while ( (i<pipeline->ncommands) && (pid=fork()) )
              i++;

            /* In the parent only. */

            if (pid>0)
              {
                /* Close all pipes. */

                for (j=0; j<pipeline->ncommands-1; j++)
                	{
                	  close (pipefds[j][0]);
                	  close (pipefds[j][1]);
                	}

                /* Wait for the last subprocess. */

                waitpid (pid, &status, 0);

              }

            /* In each subprocess. */

            if (pid==0)
              {

                /* If I'm the first process in the pipeline */
                if(i==0){

                	/* Close the "read" end of the first pipe */
                	close (pipefds[i][0]);

                	/* Redirect my output to the "write" end of the first pipe */
                	close (1);
                	dup(pipefds[i][1]);
                	close (pipefds[i][1]);


          	/* Close both ends of all the pipes I won't use, i.e. all the pipes
          	   whose indexes are greater than my own */
                	for(j=1; j<pipeline->ncommands-1; j++){
                	  close (pipefds[j][0]);
                	  close (pipefds[j][1]);
                	}
                }

                /* If I'm the last process in the pipeline */
                else if(i==pipeline->ncommands-1){


                	/* Close the "write" end of the last pipe */
                	close (pipefds[i-1][1]);

                	/* Redirect my input to the "read" end of the last pipe */
                	close (0);
                	dup(pipefds[i-1][0]);
                	close (pipefds[i-1][0]);

                	/* Close both ends of all the pipes I won't use, i.e. all the pipes
                	   except the last one */
                	for(j=0; j<pipeline->ncommands-2; j++){
                	  close (pipefds[j][0]);
                	  close (pipefds[j][1]);
                	}

                }

                /* If I'm any process other than the first or the last */
                else{

                	/* Redirect my input to the "read" end of the proper pipe, i.e. the
                	   pipe that has its index equal to mine minus 1 */
                	close (0);
                	dup(pipefds[i-1][0]);

                	/* Redirect my input to the "write" end of the proper pipe, i.e.
                	   the pipe that has its index equal to mine */
                	close (1);
                	dup(pipefds[i][1]);

                	/* Close all the ends of all the pipes */
                	for(j=0; j<pipeline->ncommands-1; j++){
                	  close (pipefds[j][0]);
                	  close (pipefds[j][1]);
                	}

                }

                /* Run the command I need to */
                execvp(pipeline->command[i][0], pipeline->command[i]);
              }
        }else{
          for (i=0; pipeline->command[i][0]; i++){
	    if(strcmp(pipeline->command[i][0],"cd")==0){

	    }else{
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
              		execvp(pipeline->command[i][0], pipeline->command[i]);
            	}else{
              		wait(&status);
            	}
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
