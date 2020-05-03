#ifndef _PROCESS_
#define _PROCESS_

#include <sys/types.h>

#define CHILD_CPU 1
#define PARENT_CPU 0

#define UNIT_T() { volatile unsigned long i; for(i=0;i<1000000UL;i++); }	

struct process{
    pid_t pid;
    char name[32];
    int t_ready;
    int t_exec;
    int timestamp;
};

int n_proc;

struct process *proc;

void proc_set_cpu(int pid, int core);

void proc_block(int pid);

void proc_wakeup(int pid);

int proc_create(struct process proc);

#endif
