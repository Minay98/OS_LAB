#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>  
#include <linux/sched.h>         
#include <linux/slab.h>          

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OS-Lab-Group");
MODULE_DESCRIPTION("Process Info Module");

static int __init process_info_init(void) {
    struct task_struct *task;  

    pr_info("Loading Process Info Module\n");
    pr_info("PID\tCPU Usage\tMemory Usage (RSS)\tCommand\n");

    for_each_process(task) {
        pid_t pid = task->pid;

        unsigned long cpu_usage = task->utime + task->stime;

        unsigned long mem_usage = task->mm ? task->mm->total_vm << (PAGE_SHIFT - 10) : 0;  
        pr_info("%d\t%lu\t\t%lu KB\t\t%s\n", pid, cpu_usage, mem_usage, task->comm);
    }

    return 0;
}

static void __exit process_info_exit(void) {
    pr_info("Removing Process Info Module\n");
}

module_init(process_info_init);
module_exit(process_info_exit);
