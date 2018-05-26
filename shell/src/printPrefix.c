#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printPrefix(){
  char cwd[5000];
  printf("[");
  printf("\033[1;34m");
  printf("%s ",getenv("USER"));
  printf("\033[0m");
  printf("->");
  printf("\033[1;32m");
  getcwd(cwd, sizeof(cwd));
  printf(" %s",cwd);
  printf("\033[0m");
  printf("]:");
}
