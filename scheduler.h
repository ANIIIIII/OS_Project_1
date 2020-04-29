#ifndef _SCHEDULER_
#define _SCHEDULER_

#include "process.h"

#define FIFO (int)1
#define RR (int)2
#define SJF (int)3
#define PSJF (int)4

char str_policy[32];
int policy;

int time;
int lasttime;
int pre_running;
int proc_running;
int n_finish;

void scheduling(struct process *proc);

#endif
