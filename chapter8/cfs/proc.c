#include <stdio.h>
#include <stdlib.h>
#include "proc.h"

process *create_process(int id, int initial_vruntime, int duration) {
    process *p = (process *)malloc(sizeof(process));
    if (!p) return NULL;
    p->id = id;
    p->vruntime = initial_vruntime;
    p->residual_duration = duration;
    return p;
}

void run_process_for_one_tick(process *p) {
    if (!p) return;
    if (p->residual_duration > 0) {
        p->residual_duration -= 1;
        p->vruntime += 1; /* simple model: vruntime++ per tick */
    }

    printf("      [tick] process id=%d, vruntime=%d, residual=%d\n",
           p->id, p->vruntime, p->residual_duration);
}

void terminate_process(process *p) {
    if (!p) return;
    p->residual_duration = 0;
}

int is_terminated(process *p) {
    if (!p) return 1;
    return p->residual_duration <= 0;
}
