#ifndef HEADER			/* Prevent duplicated inclusion. */
#define HEADER
#include <posixeg/tparse.h>
#include <posixeg/debug.h>
#include <posixeg/list.h>

void printPrefix();
void signalHandler(int signal);
int builtinCommand(char** command);
void addJob(pipeline_t *pipeline);

typedef struct job{
    int pid;
    char* command;
}job;

list_t *job_list;
pipeline_t *pipeline;
int current_pid;

#endif
