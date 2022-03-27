#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded (insmod command). */
int entryPoint(void) {
    struct task_struct *task;

    printk(KERN_INFO "Inserting ListTasksLinear\n");
    printk(KERN_INFO "Started listing tasks\n");

    for_each_process(task) { // iterate over all current tasks in the system

        /* task points to the next task on each iteration */

        printk(KERN_INFO "Name: %-20s State: %ld\tProcess ID: %d\n",
               task->comm,  // task' name
               task->state, // task's state (-1 unrunnable, 0 runnable, >0 stopped)
               task->pid);  // task's process ID
    }

    printk(KERN_INFO "Stopped listing tasks\n");
    return 0;
}

/* This function is called when the module is removed (rmmod command). */
void exitPoint(void) {
    printk(KERN_INFO "Removing ListTasksLinear\n");
}

/* Macros for registering module entry and exit points. */
module_init(entryPoint);
module_exit(exitPoint);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks linearly");
MODULE_AUTHOR("NTUT OS");
