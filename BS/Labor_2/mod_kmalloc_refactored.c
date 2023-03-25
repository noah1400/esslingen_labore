#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noah");
MODULE_DESCRIPTION("KMALLOC MODULE");

//variables
static size_t alloc_size;
char **kmallocArr;

// read parameters from instruction line
module_param(alloc_size, uint, 0644);
MODULE_PARM_DESC(alloc_size, "Size of the memory block to allocate");

// prototype
// completion handler
static void completion_handler(unsigned long data);

static void completion_handler(unsigned long data)
{
    printk(KERN_INFO "Completion handler\n");
    unsigned long flags;
    unsigned long start, end, total;
    spinlock_t lock;

    spin_lock_irqsave(&lock, flags);
    start = rdtsc();
    kmallocArr = kmalloc(alloc_size, GFP_KERNEL);
    kfree(kmallocArr);
    end = rdtsc();
    total = end - start;
    printk(KERN_INFO "Total cycles: %lu\n", total);
    spin_unlock_irqrestore(&lock, flags);
}

// module init function
static int kmalloc_init(void){
    printk(KERN_INFO "KMALLOC MODULE LOADED\n");
    // Validating the parameters
    if (alloc_size <= 0) {
        printk(KERN_INFO "Invalid parameter\n");
        return -1;
    }
    spin_lock_init(&lock);
    // Setting up completion handler
    complete_and_exit(&completion_handler, 0);
}

// module exit function
static void kmalloc_exit(void){
    printk(KERN_INFO "KMALLOC MODULE UNLOADED\n");
}

// register init and exit functions
module_init(kmalloc_init);
module_exit(kmalloc_exit);