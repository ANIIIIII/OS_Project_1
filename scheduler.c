#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include "scheduler.h"
#include "process.h"
#include "policy.h"

int proc_next(struct process *proc){
	int next = -1;
	//policy.h
	if(policy == FIFO){
		next = FIFO_next(proc_running);
	}else if(policy == SJF){
		next = SJF_next(proc_running);
	}else if(policy == PSJF){
		next = PSJF_next(proc_running);
	}else if(policy == RR){
		next = RR_next(proc_running);
	}
	return next;
}

void scheduling(struct process *proc){

	//initialization

	//stable sort
	for(int i = 0; i < n_proc; i++){
		for(int j = i + 1; j < n_proc; j++){
			if(proc[i].t_ready > proc[j].t_ready){
				struct process temp = proc[i];
				proc[i] = proc[j];
				proc[j] = temp;
			}
		}
	}
    proc_set_cpu(getpid(), PARENT_CPU);

	time = 0;
	lasttime = 0;
	pre_running = -1;
	proc_running = -1;
	int count = 0;

	//schedule process
    while(1){
		//retrieve process
        if(proc_running != -1 && proc[proc_running].t_exec == 0){
			waitpid(proc[proc_running].pid, NULL, 0);
			printf("%s %d\n", proc[proc_running].name, proc[proc_running].pid);
			pre_running = proc_running;
			proc_running = -1;
			count++;
			if(count == n_proc){
                break; //finish
            }
		}

		//create process
        for(int i = 0; i < n_proc; i++){
			if(proc[i].t_ready == time){
				proc[i].pid = proc_create(proc[i]);
				proc_block(proc[i].pid);
			}
		}

		//decide next process
        int next = proc_next(proc);
		if(next != -1 && proc_running != next){
			proc_wakeup(proc[next].pid);
			proc_block(proc[proc_running].pid);
			pre_running = proc_running;
			proc_running = next;
			lasttime = time;
		}

        UNIT_T();
		
        if(proc_running != -1){
			proc[proc_running].t_exec--;
        }
		time++;
    }
}
