#include <linux/sched.h>
#include <linux/init.h> // 定義了驅動的初始化和清除相關的函式
#include <linux/kernel.h> // 定義了經常用到的函式原型及巨集定義
#include <linux/module.h> // 定義了核心模組相關的函式、變數及巨集
#include <linux/init_task.h>

// standard practice in developing kernel modules
MODULE_LICENSE("GPL"); // GNU General Public License
MODULE_AUTHOR("OS Team 5");

/* the function that is invoked when the module is loaded into the kernel. */
int linear_init(void) {
	struct task_struct *task; // Pointer to the task whose information will be printed
	
	printk(KERN_INFO "********** Start **********\n"); // the priority is KERN_INFO, which is defined as an informational message

	for_each_process(task) {   // for_each_process() allows iteration over all current tasks in the system
		printk(KERN_INFO "Task Name: %-20s Task State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
		// task->comm -> task's name
		// task->state -> task's state (-1 is unrunnable, 0 is runnable, > 0 is stopped)
		// task->pid -> task's process ID
	}
	
	printk(KERN_INFO "********** Stop **********\n");
	return 0;
}

/* the function that is invoked When the module is removed from the kernel. */
void linear_exit(void) {
	printk(KERN_INFO "********** Exit **********\n");
}

module_init(linear_init); // defines which function (entry point) is to be called at module insertion time or at boot time（it will release its memory after executing） 
module_exit(linear_exit); // the function to be called at module removal time and user called 'rmmod' instruction 

