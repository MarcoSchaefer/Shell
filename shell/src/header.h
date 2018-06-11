#ifndef HEADER			/* Prevent duplicated inclusion. */
#define HEADER
#include <posixeg/tparse.h>
#include <posixeg/debug.h>
#include <posixeg/list.h>
#include <unistd.h>

void printPrefix();
void signalHandler(int signal);
int builtinCommand(char** command);
void addJob(pipeline_t *pipeline);

typedef struct job{
    int pid;
    char* command;
    int status;
    /*STATUS: [0]Foregroung [1]Background [2]Stopped*/
}job;

list_t *job_list;
pipeline_t *pipeline;
int current_pid;
pid_t shell_group;

#endif
