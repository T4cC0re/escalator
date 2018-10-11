#include <linux/module.h>
#include <linux/kernel.h>
#include "driver.c"
#include "escalate.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hendrik 'T4cC0re' Meyer");
MODULE_DESCRIPTION("Sudo after the fact! / Escalate running processes to root");
MODULE_VERSION("0.1");

static int pid = 0;

module_param(pid, int, S_IRUGO);
MODULE_PARM_DESC(pid, "Process ID to escalate");

static int __init init(void) {
    printk(KERN_INFO "escalator: Init\n");

    if (pid <= 1) {
        printk(KERN_ALERT "escalator: pid not valid.");
        return -1;
    }

    escalate(pid);

    return escalator_driver_init();
}

static void __exit cleanup(void) {
    printk(KERN_INFO "escalator: Asked to unload. Cleaning up...\n");

    escalator_driver_cleanup();

    printk(KERN_INFO "escalator: Exit!\n");
}

module_init(init);
module_exit(cleanup);
