#include <linux/init.h>       // For the module_init and module_exit macros
#include <linux/module.h>     // For defining modules
#include <linux/printk.h>     // For using print functions

/* This function is called when the module is loaded */
static int __init simple_init(void)
{
    pr_info("Loading simple module\n");
    return 0; // Returning 0 indicates successful loading
}

/* This function is called when the module is unloaded */
static void __exit simple_exit(void)
{
    pr_info("Unloading simple module\n");
}

/* Registering functions as entry and exit points */
module_init(simple_init);
module_exit(simple_exit);

/* Adding meta information to the module */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple module for testing");
MODULE_AUTHOR("Operating Systems Lab Group");
