#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*Returns 1 if the command received is a builtin command. Returns 0 if isn't*/
int builtinCommand(char** command){
    int result;
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
    return 0;
}
