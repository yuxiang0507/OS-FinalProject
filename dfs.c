#include <linux/sched.h>
#include <linux/init.h> //�w�q�F�X�ʪ���l�ƩM�h�X�������禡 
#include <linux/kernel.h> //�w�q�F�g�`�Ψ쪺�禡�쫬�Υ����w�q 
#include <linux/module.h> //�w�q kernel module�������禡�B�ܼƤΥ��� 
#include <linux/init_task.h>

// standard practice in developing kernel modules
MODULE_LICENSE("GPL"); // GNU General Public License
MODULE_AUTHOR("OS Team 5");

// Depth-First Search
void dfs(struct task_struct *task) {
	struct task_struct *child; // Pointer to child whose information will be printed
	struct list_head *list; // linked-list 
	
	// the priority is KERN_INFO, which is defined as an informational message
	printk(KERN_INFO "Task Name: %-20s Task State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
	// task->comm -> task' name
	// task->state -> task's state (-1 is unrunnable, 0 is runnable, > 0 is stopped)
	// task->pid -> task's process ID
	
	// At each iteration of list_for_each, the first parameter is set to the list structure of the next child.
	list_for_each(list, &task -> children) { // use that value to obtain each structure in the list using list_entry() macro
		child = list_entry(list, struct task_struct, sibling);
		// Get child, child points to the next child in the list (sibling's member is pointed by 'children.next')
		dfs(child); // �H���j���覡�A��child����dfs() 
	}
}

/* the function that is invoked when the module is loaded into the kernel. */
int dfs_init(void) {
	
	printk(KERN_INFO "********** Start Part II**********\n");
	
	dfs(&init_task); // DFS starts init_task
	
	printk(KERN_INFO "********** Stop **********\n");
	return 0;
}

/* the function that is invoked When the module is removed from the kernel. */
void dfs_exit(void) {
	printk(KERN_INFO "********** Exit **********\n");
}

module_init(dfs_init);
/* defines which function (entry point) is to be called at module insertion time or
 at boot time�]it will release its memory after executing�^ */ 
module_exit(dfs_exit);
// the function to be called at module removal time and user called 'rmmod' instruction 

