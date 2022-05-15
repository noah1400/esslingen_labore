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
    void *ptr;
    start = rdtsc();
    for (i = 0; i < loop_cnt; i++) {
        ptr = kmalloc(alloc_size, GFP_KERNEL);
        kfree(ptr);
    }
    end = rdtsc();
    total = end - start;
    printk(KERN_INFO "Total time: %lu\n", total);
}

// module init function
static int kmalloc_init(void){
    printk(KERN_INFO "KMALLOC MODULE LOADED\n");
    tasklet_schedule(&tasklet);
    return 0;
}

// module exit function
static void kmalloc_exit(void){
    printk(KERN_INFO "KMALLOC MODULE UNLOADED\n");
    tasklet_kill(&tasklet);
}

// register init and exit functions
module_init(kmalloc_init);
module_exit(kmalloc_exit);