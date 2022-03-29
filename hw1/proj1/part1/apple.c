/**
 * @file apple.c
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
 *
 * We use `static` to mark this function to be a static function because
 * a static function has a scope that is limited to its object file.
 * So that means this function can only be called in this file, if try to call it on others, a reference error will occurred.
 *
 * For the reason why this function should return an integer, please refer to here for more details:
 * https://github.com/torvalds/linux/blob/763978ca67a3d7be3915e2035e2a6c331524c748/include/linux/module.h#L76=
 *
 * @return int: indicates the module load event callback is executed successfully.
 */
static int hello_init(void) {
    // Write a simple msg into kernel ring buffer.
    // Please refer to this page for more details:
    // https://www.kernel.org/doc/html/latest/core-api/printk-basics.html?highlight=printk#c.printk
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

    // Return a successfully-executed code.
    return 0;
}

/**
 * @brief The callback function of kernel module unload event.
 * It will be called and write a msg to kernel ring buffer after this module has already unloaded.
 *
 * For the reason why this function should return void, please refer to here for more details:
 * https://github.com/torvalds/linux/blob/763978ca67a3d7be3915e2035e2a6c331524c748/include/linux/module.h#L77=
 */
static void hello_exit(void) {
    // Write a simple msg into kernel ring buffer.
    printk(KERN_INFO "Bye !\n");
}

// Register the module callback functions on module (did) load event.
module_init(hello_init);

// Register the module callback functions on module (did) unload event.
module_exit(hello_exit);
