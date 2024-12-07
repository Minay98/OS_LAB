
typedef struct{
    int id;
    int vruntime;
    int residual_duration;
} process;

process *create_process(int id, int vruntime, int residual_duration);
void run_process_for_one_tick(process *p);
void terminate_process(process *p);
int is_terminated(process *p);
