#ifndef PROC_H
#define PROC_H

/* Very small "process" abstraction used by the CFS scheduler lab. */

typedef struct process {
    int id;
    int vruntime;           /* virtual runtime */
    int residual_duration;  /* how many ticks left to finish */
} process;

/* Creates a new process with given id, initial vruntime and execution duration. */
process *create_process(int id, int initial_vruntime, int duration);

/* Runs the process for exactly one tick: decreases residual_duration and
 * increases vruntime.
 */
void run_process_for_one_tick(process *p);

/* Forces termination of the process (residual_duration = 0). */
void terminate_process(process *p);

/* Returns non-zero if the process is finished. */
int is_terminated(process *p);

#endif /* PROC_H */
