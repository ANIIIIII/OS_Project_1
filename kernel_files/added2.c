#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/types.h>
#include <linux/uaccess.h> 
#include <linux/compiler.h>

asmlinkage long sys_added2(struct timespec __user *t){
	struct timespec temp;
    	getnstimeofday(&temp);
	copy_to_user(t, &temp, sizeof(struct timespec));
	return 0;
}
