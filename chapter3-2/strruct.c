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

static int __init list_init(void)
{
    struct birthday *bday;
    int i;

    pr_info("Linked list module loaded\n");

    // Add some elements to the list
    for (i = 1; i <= 3; i++) {
        bday = kmalloc(sizeof(*bday), GFP_KERNEL);
        if (!bday)
            return -ENOMEM;

        bday->day = i;
        bday->month = i;
        bday->year = 2000 + i;

        INIT_LIST_HEAD(&bday->list); // Initialize the list field

        list_add_tail(&bday->list, &birthday_list); // Add to the end of the list
        pr_info("Added birthday: %d/%d/%d\n", bday->day, bday->month, bday->year);
    }

    // Traverse and display the list elements
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {
        pr_info("Current birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

static void __exit list_exit(void)
{
    struct birthday *ptr, *tmp;

    pr_info("Linked list module unloaded\n");

    // Traverse and free the memory of list elements
    list_for_each_entry_safe(ptr, tmp, &birthday_list, list) {
        pr_info("Removing birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(list_init);
module_exit(list_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sample module using list_head");
MODULE_AUTHOR("Operating Systems Lab Team");
