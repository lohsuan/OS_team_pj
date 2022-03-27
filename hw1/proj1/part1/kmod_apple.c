/**
 * @file kmod_apple.c
 * @author Xanonymous
 * @brief A simple kernel module to test the kernel module load/unload process.
 * @version 0.1
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("A simple kernel module to test the kernel module load/unload process.");
MODULE_LICENSE("GPL");

int hello_init(void) {
    printk(KERN_INFO "Hello world !\n");
    return 0;
}

void hello_exit(void) {
    printk(KERN_INFO "Bye !\n");
}

module_init(hello_init);
module_exit(hello_exit);