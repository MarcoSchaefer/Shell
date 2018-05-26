#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printPrefix(){
  printf("[");
  printf("\033[1;34m");
  printf("%s ",getenv("USER"));
  printf("\033[0m");
  printf("->");
  printf("\033[1;31m");
  printf(" %s",getenv("PWD"));
  printf("\033[0m");
  printf("]:");
}
