/**
 * @file banana.c
 * @author Xanonymous
 * @brief A simple module that does some operations related to the linked list when it is loaded and unload.
 * @version 0.1
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>

MODULE_DESCRIPTION("A simple module that does some operations related to the linked list when it is loaded and unload.");
MODULE_LICENSE("GPL");

#define LISTNAME birthday_list

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

/**
 * @brief Construct a new list_head object.
 *
 * Which is equal to this:
 * ```
 * struct list_head name = LIST_HEAD_INIT(name)
 * ```
 * Please refer to: https://github.com/torvalds/linux/blob/763978ca67a3d7be3915e2035e2a6c331524c748/include/linux/list.h#L25=
 *
 * And the list_head structure is defined as this:
 * ```
 * struct list_head {
 *  struct list_head *next, *prev;
 * };
 * ```
 * Please refer to: https://github.com/torvalds/linux/blob/763978ca67a3d7be3915e2035e2a6c331524c748/include/linux/types.h#L178=
 */
static LIST_HEAD(LISTNAME);

/**
 * @brief Create a Birthday Node With objects
 * The created node will be appended to the tail of the linked list.
 * @param day
 * @param month
 * @param year
 */
void createBirthdayNodeWith(const int day, const int month, const int year) {
    struct birthday *_b;

    // Apply & clear the kernel memory.
    //
    // The kzalloc() function is very similar to kmalloc(),
    // the parameters and return values are the same,
    // it can be said that the former is a variant of the latter,
    // because kzalloc() is actually just an additional __GFP_ZERO flag.
    _b = kzalloc(sizeof(*_b), GFP_KERNEL);

    _b->day = day;
    _b->month = month;
    _b->year = year;

    /**
     * Initialize a list_head structure.
     * @list: list_head structure to be initialized.
     *
     * Initializes the list_head to point to itself.  If it is a list header,
     * the result is an empty list.
     */
    INIT_LIST_HEAD(&_b->list);

    /**
     * Add a new entry.
     * @new: new entry to be added
     * @head: list head to add it before
     *
     * Insert a new entry before the specified head.
     * This is useful for implementing queues.
     */
    list_add_tail(&_b->list, &LISTNAME);
}

/**
 * @brief Create Birthday linked list, and traverse it.
 *
 * @return int
 */
static int createAndTraverseBirthdays(void) {
    struct birthday *birthdayPtr = NULL;

    printk(KERN_INFO "Creating birthday list\n");

    createBirthdayNodeWith(31, 9, 2000);
    createBirthdayNodeWith(28, 3, 2001);
    createBirthdayNodeWith(18, 2, 2001);
    createBirthdayNodeWith(4, 1, 2000);
    createBirthdayNodeWith(9, 11, 1999);

    printk(KERN_INFO "Traversing birthday list\n");

    /**
     * iterate over list of given type.
     * @pos:	the type * to use as a loop cursor.
     * @head:	the head for your list.
     * @member:	the name of the list_head within the struct.
     */
    list_for_each_entry(birthdayPtr, &LISTNAME, list) {
        printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n", birthdayPtr->month, birthdayPtr->day, birthdayPtr->year);
    }

    return 0;
}

/**
 * @brief Traverse, and remove all nodes on the linked list.
 *
 */
static void removeAndFreeBirthdays(void) {
    struct birthday *birthdayPtr = NULL;
    struct birthday *next = NULL;

    printk(KERN_INFO "Removing module\n");

    /**
     * iterate over list of given type safe against removal of list entry.
     * @pos:	the type * to use as a loop cursor.
     * @n:		another type * to use as temporary storage
     * @head:	the head for your list.
     * @member:	the name of the list_head within the struct.
     */
    list_for_each_entry_safe(birthdayPtr, next, &LISTNAME, list) {
        printk(KERN_INFO "REMOVING BIRTHDAY: Month: %d Day: %d Year: %d\n", birthdayPtr->month, birthdayPtr->day, birthdayPtr->year);
        list_del(&birthdayPtr->list);
        kfree(birthdayPtr);
    }
}

module_init(createAndTraverseBirthdays);
module_exit(removeAndFreeBirthdays);
