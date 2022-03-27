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

#include <linux/module.h>

MODULE_DESCRIPTION("A simple kernel module to test the kernel module load/unload process.");
MODULE_LICENSE("GPL");

/**
 * @brief The callback function of kernel module load event.
 * It will be called and write a msg to kernel ring buffer after this module has already loaded.
 * @return int: indicates the module load event callback is executed successfully.
 */
int hello_init(void) {
    // Write a simple msg into kernel ring buffer.
    //
    // `KERN_INFO` is a category code that identifies the category of this message.
    //
    // There are many other categories such as:
    // KERN_EMERG   -> system is unusable
    // KERN_ALERT   -> action must be taken immediately
    // KERN_CRIT    -> critical conditions
    // KERN_ERR     -> error conditions
    // KERN_WARNING -> warning conditions
    // KERN_NOTICE  -> normal but significant condition
    // KERN_INFO    -> informational
    // KERN_DEBUG   -> debug-level messages
    //
    // Please refer to this file for more details:
    // https://github.com/torvalds/linux/blob/5bfc75d92efd494db37f5c4c173d3639d4772966/include/linux/kern_levels.h
    printk(KERN_INFO "Hello world !\n");
    return 0;
}

/**
 * @brief The callback function of kernel module unload event.
 * It will be called and write a msg to kernel ring buffer after this module has already unloaded.
 */
void hello_exit(void) {
    // Write a simple msg into kernel ring buffer.
    printk(KERN_INFO "Bye !\n");
}

// Register the module callback functions on module (did) load event.
module_init(hello_init);

// Register the module callback functions on module (did) unload event.
module_exit(hello_exit);
