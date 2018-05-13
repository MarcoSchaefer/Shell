#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <posixeg/tparse.h>
#include <posixeg/debug.h>

void init(char **SHELL_PREFIX){
  FILE *fp;
  char buffer[5000];
  char *iter;

  /* Open the command for reading. */
  fp = popen("who", "r");
  if (fp == NULL) {
    printf("Command `who` not found \n");
    printf("Are you using linux?\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  fgets(buffer, sizeof(buffer)-1, fp);

  iter = strtok(buffer," ");
  *SHELL_PREFIX = (char*)malloc(sizeof(char)*(strlen(iter)+3));
  sprintf(*SHELL_PREFIX,"[%s]:",iter);
  /* close */
  pclose(fp);
}
