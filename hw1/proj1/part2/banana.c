/**
 * @file banana.c
 * @author Xanonymous
 * @brief
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

MODULE_DESCRIPTION("");
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

void createBirthdayNodeWith(const int day, const int month, const int year) {
    struct birthday *_b;
    _b = kzalloc(sizeof(*_b), GFP_KERNEL);
    _b->day = day;
    _b->month = month;
    _b->year = year;
    INIT_LIST_HEAD(&_b->list);
    list_add_tail(&_b->list, &LISTNAME);
}

static int createAndTraverseBirthdays(void) {
    printk(KERN_INFO "Creating birthday list\n");

    createBirthdayNodeWith(31, 9, 2000);
    createBirthdayNodeWith(28, 3, 2001);
    createBirthdayNodeWith(18, 2, 2001);
    createBirthdayNodeWith(4, 1, 2000);
    createBirthdayNodeWith(9, 11, 1999);

    printk(KERN_INFO "Traversing birthday list\n");

    struct birthday *birthdayPtr;

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

static void removeAndFreeBirthdays(void) {
    printk(KERN_INFO "Removing module\n");

    struct birthday *birthdayPtr, *next;

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
