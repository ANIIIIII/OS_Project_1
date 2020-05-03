#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#define TIME_Q (int)500

int FIFO_next(int proc_running){
    if(proc_running != -1) return proc_running;

	int ret = -1;

	for(int i = 0; i < n_proc; i++){
		if(proc[i].pid == -1 || proc[i].t_exec == 0)
			continue;
		if(ret == -1 || proc[i].t_ready < proc[ret].t_ready)
			ret = i;
	}
	return ret;
}

int SJF_next(int proc_running){
    if(proc_running != -1) return proc_running;

	int ret = -1;
	for(int i = 0; i < n_proc; i++){
		if(proc[i].pid == -1 || proc[i].t_exec == 0) 
            continue;
		if(ret == -1 || proc[i].t_exec < proc[ret].t_exec)
		    ret = i;
	}
	return ret;
}

int PSJF_next(int proc_running){
	int ret = proc_running;
	for(int i = 0; i < n_proc; i++){
		if(proc[i].pid == -1 || proc[i].t_exec == 0) 
            continue;
		if(ret == -1 || proc[i].t_exec < proc[ret].t_exec)
			ret = i;
	}
	return ret;
}

int RR_next(int proc_running){
	int ret = -1;
	if(proc_running == -1){
		for(int i = 0; i < n_proc; i++){
			if(proc[i].pid == -1 || proc[i].t_exec == 0){
				continue;
			}
			if(ret == -1 || proc[ret].timestamp > proc[i].timestamp){
				ret = i;
			}
		}
	}else if((time - lasttime) % TIME_Q == 0){
		for(int i = 1; i <= n_proc; i++){
			int j = (proc_running + i) % n_proc;
			if(proc[j].pid == -1 || proc[j].t_exec == 0){
				continue;
			}
			if(ret == -1 || proc[ret].timestamp > proc[j].timestamp){
				ret = j;
			}
		}
	}else
		ret = proc_running;
	
	
	return ret;
}
