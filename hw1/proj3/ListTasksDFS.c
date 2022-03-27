#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/task.h>

void dfs(struct task_struct *task) {
    struct task_struct *child; // pointer to the next child
    struct list_head *list;    // children

    printk(KERN_INFO "Name: %-20s State: %ld\tProcess ID: %d\n", task->comm, task->state, task->pid);

    list_for_each(list, &task->children) {                     // iterate over children of init_list
        child = list_entry(list, struct task_struct, sibling); // get child
        /* child points to the next child in the list */
        dfs(child);
    }
}

/* This function is called when the module is loaded. */
int entryPoint(void) {
    printk(KERN_INFO "Inserting ListTasksDFS\n");

    printk(KERN_INFO "Started listing tasks\n");

    dfs(&init_task); // DFS start from init_task

    printk(KERN_INFO "Stopped listing tasks\n");
    return 0;
}

/* This function is called when the module is removed. */
void exitPoint(void) {
    printk(KERN_INFO "Removing ListTasksDFS\n");
}

/* Macros for registering module entry and exit points. */
module_init(entryPoint);
module_exit(exitPoint);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks using DFS");
MODULE_AUTHOR("NTUT OS");
