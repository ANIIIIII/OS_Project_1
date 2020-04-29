#ifndef _POLICY_
#define _POLICY_

int FIFO_next(int proc_running);

int SJF_next(int proc_running);

int PSJF_next(int proc_running);

int RR_next(int proc_running);

#endif
