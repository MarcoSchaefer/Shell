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


/* void test(void); */

int go_on = 1;			/* This variable controls the main loop. */

int main (int argc, char **argv)
{
  char* SHELL_PREFIX;
  buffer_t *command_line;
  int i, j, aux, pid, status, fd;
  pipeline_t *pipeline;

  fd = -1;

  init(&SHELL_PREFIX);
  command_line = new_command_line ();
  pipeline = new_pipeline ();

  /* This is the main loop. */
  while (go_on){

      printf ("%s ", SHELL_PREFIX);
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

        for (i=0; pipeline->command[i][0]; i++){
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

  close(fd);
  release_command_line (command_line);
  release_pipeline (pipeline);

  return EXIT_SUCCESS;
}
