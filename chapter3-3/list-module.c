#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list); // Define and initialize the linked list

static int __init list_module_init(void)
{
    struct birthday *b1, *b2, *b3;

    pr_info("Linked list module loaded\n");

    // Create and add the first member
    b1 = kmalloc(sizeof(*b1), GFP_KERNEL);
    if (!b1)
        return -ENOMEM;
    b1->day = 2;
    b1->month = 8;
    b1->year = 1995;
    INIT_LIST_HEAD(&b1->list);
    list_add_tail(&b1->list, &birthday_list);
    pr_info("Added birthday: %d/%d/%d\n", b1->day, b1->month, b1->year);

    // Create and add the second member
    b2 = kmalloc(sizeof(*b2), GFP_KERNEL);
    if (!b2)
        return -ENOMEM;
    b2->day = 15;
    b2->month = 12;
    b2->year = 1990;
    INIT_LIST_HEAD(&b2->list);
    list_add_tail(&b2->list, &birthday_list);
    pr_info("Added birthday: %d/%d/%d\n", b2->day, b2->month, b2->year);

    // Create and add the third member
    b3 = kmalloc(sizeof(*b3), GFP_KERNEL);
    if (!b3)
        return -ENOMEM;
    b3->day = 30;
    b3->month = 4;
    b3->year = 1985;
    INIT_LIST_HEAD(&b3->list);
    list_add_tail(&b3->list, &birthday_list);
    pr_info("Added birthday: %d/%d/%d\n", b3->day, b3->month, b3->year);

    // Traverse and display the list elements
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {
        pr_info("Existing birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

static void __exit list_module_exit(void)
{
    struct birthday *ptr, *tmp;

    pr_info("Linked list module unloaded\n");

    // Traverse and free the memory of the list elements
    list_for_each_entry_safe(ptr, tmp, &birthday_list, list) {
        pr_info("Removing birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(list_module_init);
module_exit(list_module_exit);

MODULE_LICENSE("GPL")
