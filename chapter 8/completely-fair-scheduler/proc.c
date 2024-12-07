#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "proc.h"

process *create_process(int id, int vruntime, int residual_duration){
    process *p;

    p = (process *) malloc(sizeof(process));
    if(p != NULL){
        p->id = id;
        p->vruntime = vruntime;
        p->residual_duration = residual_duration;
    }
    return p;
}

void run_process_for_one_tick(process *p){
    if(p->residual_duration == 0){
        fprintf(stderr, "process: %d is already terminated\n", p->id);
        return;
    }
    printf("process %d is running\tcurrent vruntime: %d\tcurrent residual_duration: %d\n", p->id, p->vruntime, p->residual_duration);
    p->residual_duration -= 1;
    p->vruntime += 1;
    printf("after running for one tick:\tvruntime: %d\tresidual_duration: %d\n", p->vruntime, p->residual_duration);
    if(p->residual_duration == 0){
        terminate_process(p);
    }
}

void terminate_process(process *p){
    printf("process %d terminated.\n", p->id);
    free(p);
}

int is_terminated(process *p){
    return p->residual_duration == 0;
}