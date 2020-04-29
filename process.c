#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "process.h"

#define PRINTK (int)333
#define GETNSTIMEOFDAY (int)334

void proc_set_cpu(int pid, int core){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	sched_setaffinity(pid, sizeof(mask), &mask);
}

void proc_block(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	sched_setscheduler(pid, SCHED_IDLE, &param);
}

void proc_wakeup(int pid){
	struct sched_param param;
	param.sched_priority = 99;
    sched_setscheduler(pid, SCHED_FIFO, &param);
}

void get_time(struct timespec *temp){
	syscall(GETNSTIMEOFDAY, temp);
}

void print_time(struct timespec start, struct timespec end){
	syscall(PRINTK, getpid(), start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
}

int proc_create(struct process proc){
	int pid;
	if((pid = fork()) == 0){
		struct timespec start;
		get_time(&start);

		for(int i = 0; i < proc.t_exec; i++){
			UNIT_T();
		}
		struct timespec end;
		get_time(&end);

		print_time(start, end);
		_exit(0);
	}
	proc_set_cpu(pid, CHILD_CPU);

	return pid;
}
