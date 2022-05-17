/*
*   linux kernel module that measures the kmalloc() and kfree() performance
*   takes 2 arguments:
*   1. the number of iterations to run the test
*   2. the size of the memory block to allocate
*
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/interrupt.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noah");
MODULE_DESCRIPTION("KMALLOC MODULE");

//variables
static int size = sizeof(char*);
char **kmallocArr;

// read parameters from instruction line
static int loop_cnt = 0;
static int alloc_size = 0;
module_param(loop_cnt, int, 0);
module_param(alloc_size, int, 0);
// Parameter Description:
// loop_cnt: number of iterations to run the test
// alloc_size: size of the memory block to allocate
MODULE_PARM_DESC(loop_cnt, "Number of iterations to run the test");
MODULE_PARM_DESC(alloc_size, "Size of the memory block to allocate");

// prototype
// tasklet handler
static void tasklet_handler(unsigned long data);
// register tasklet
DECLARE_TASKLET_OLD(tasklet, tasklet_handler);

// tasklet handler
// measures the kmalloc() and kfree() performance
static void tasklet_handler(unsigned long data)
{
    printk(KERN_INFO "Tasklet handler\n");
    int i;
    unsigned long start, end, total;
    start = rdtsc();
    for (i = 0; i < loop_cnt; i++) {
        kmallocArr[i] = kmalloc(alloc_size, GFP_KERNEL);
    }
    end = rdtsc();
    total = end - start;
    printk(KERN_INFO "Total cycles: %lu\n", total);
}

// module init function
static int kmalloc_init(void){
    printk(KERN_INFO "KMALLOC MODULE LOADED\n");
    // Validating the parameters
    if (loop_cnt <= 0 || alloc_size <= 0) {
        printk(KERN_INFO "Invalid parameters\n");
        return -1;
    }
    // Setting up kmallocArr
    kmallocArr = kmalloc_array(loop_cnt, size, GFP_KERNEL);
    tasklet_schedule(&tasklet);
    return 0;
}

// module exit function
static void kmalloc_exit(void){
    printk(KERN_INFO "KMALLOC MODULE UNLOADED\n");
    tasklet_kill(&tasklet);
    // Freeing kmallocArr
    int i;
    for (i = 0; i < loop_cnt; i++) {
        kfree(kmallocArr[i]);
    }
}

// register init and exit functions
module_init(kmalloc_init);
module_exit(kmalloc_exit);