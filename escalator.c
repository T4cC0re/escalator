#include <linux/module.h>
#include <linux/kernel.h>
#include "driver.c"

MODULE_LICENSE("Apache-2.0");
MODULE_AUTHOR("Hendrik 'T4cC0re' Meyer");
MODULE_DESCRIPTION("Sudo after the fact! / Escalate running processes to root");
MODULE_VERSION("0.1");

static int pid = 0;

module_param(pid, int, S_IRUGO);
MODULE_PARM_DESC(pid, "Process ID to escalate on load");

static int __init init(void) {
    printk(KERN_INFO "escalator: Init\n");

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
