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

    if(pre_running == -1 && proc_running == -1){
		for(int i = 0; i < n_proc; i++){
			if(proc[i].pid != -1 && proc[i].t_exec > 0){
				ret = i;
				break;
			}
		}
	}else if(proc_running == -1){
        for(int i = 1; i <= n_proc; i++){
			if(proc[(pre_running + i) % n_proc].pid != -1 && proc[(pre_running + i) % n_proc].t_exec > 0){
				ret = (pre_running + i) % n_proc;
				break;
			}
		}
    }else if(time != lasttime && (time - lasttime) % TIME_Q == 0){
		ret = (proc_running + 1) % n_proc;
		while(proc[ret].pid == -1 || proc[ret].t_exec == 0)
			ret = (ret + 1) % n_proc;
    }else 
        ret = proc_running;
	return ret;
}
