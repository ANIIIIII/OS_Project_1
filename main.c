#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "process.h"
#include "scheduler.h"

int main(void){
    scanf("%s", str_policy);
    scanf("%d", &n_proc);

    proc = (struct process *)malloc(n_proc * sizeof(struct process));
    
    for(int i = 0; i < n_proc; i++){
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
        proc[i].pid = -1;
    }

    if(strcmp(str_policy, "FIFO") == 0){
        policy = FIFO;
    }else if(strcmp(str_policy, "RR") == 0){
        policy = RR;
    }else if(strcmp(str_policy, "SJF") == 0){
        policy = SJF;
    }else if(strcmp(str_policy, "PSJF") == 0){
        policy = PSJF;
    }
    
    scheduling(proc);

    return 0;
}
