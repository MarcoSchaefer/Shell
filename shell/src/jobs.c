#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <posixeg/tparse.h>
#include <posixeg/debug.h>
#include <posixeg/list.h>

void addJob(pipeline_t *pipeline){
    list_node_t *new_node;
    job* new_job;

    if(current_pid<=0){
        return;
    }
    if(pipeline->ncommands<1){
        return;
    }
    fflush(stdout);
    new_node = (list_node_t*)malloc(sizeof(list_node_t));
    new_node = append_node (job_list);
    new_job = (job*)malloc(sizeof(job));
    new_job->command = (char*)malloc(sizeof(char)*(strlen(pipeline->command[0][0])+1));
    new_job->command = strdup(pipeline->command[0][0]);
    new_job->pid = current_pid;
    new_node->value = new_job;
}

void delJob(){

}
