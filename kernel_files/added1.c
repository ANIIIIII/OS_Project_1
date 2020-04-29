#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage long sys_added1(int a, unsigned long b, unsigned long c, unsigned long d, unsigned long e){
	printk("[Project1] %d %lu.%09lu %lu.%09lu\n", a, b, c, d, e);
	return 0;
}
