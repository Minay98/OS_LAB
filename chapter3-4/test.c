#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/types.h>


static short my_short = 0;
static int my_int = 0;
static long my_long = 0;
static char *my_string = "default";
static int my_array[5];
static int arr_argc = 0; 

module_param(my_short, short, S_IRUGO);
MODULE_PARM_DESC(my_short, "A short integer parameter");

module_param(my_int, int, S_IRUGO);
MODULE_PARM_DESC(my_int, "An integer parameter");

module_param(my_long, long, S_IRUGO);
MODULE_PARM_DESC(my_long, "A long integer parameter");

module_param(my_string, charp, S_IRUGO);
MODULE_PARM_DESC(my_string, "A string parameter");

module_param_array(my_array, int, &arr_argc, S_IRUGO);
MODULE_PARM_DESC(my_array, "An array of integers");

static int __init param_module_init(void)
{
    int i;
    pr_info("Loading module with parameters:\n");
    pr_info("my_short: %hd\n", my_short);
    pr_info("my_int: %d\n", my_int);
    pr_info("my_long: %ld\n", my_long);
    pr_info("my_string: %s\n", my_string);

    for (i = 0; i < arr_argc; i++)
    {
        pr_info("my_array[%d]: %d\n", i, my_array[i]);
    }

    return 0;
}

static void __exit param_module_exit(void)
{
    pr_info("Removing module with parameters\n");
}

module_init(param_module_init);
module_exit(param_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OS-Lab-Group");
MODULE_DESCRIPTION("A module with various parameter types");
//run:
//sudo insmod module_name.ko my_short=10 my_int=100 my_long=1000 my_string="Hello, Kernel!" my_array=1,2,3,4,5
//log:
//dmesg | tail
