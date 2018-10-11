#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hendrik 'T4cC0re' Meyer");
MODULE_DESCRIPTION("Sudo after the fact! / Escalate running processes to root");
MODULE_VERSION("0.1");

static int pid = 0;

module_param(pid, int, S_IRUGO);
MODULE_PARM_DESC(pid, "Process ID to escalate");

struct task_struct* foo;
struct cred* scred;

struct task_struct* task;
struct cred* credentials;
struct cred* real_credentials;

static escalate(int pid) {

    printk(KERN_INFO "escalator: Escalation triggered");

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_INFO "escalator: unable to retrieve task_struct");
        return;
    }
    credentials = task->cred;
    if (credentials == NULL) {
        printk(KERN_INFO "escalator: unable to retrieve cred");
        return;
    }

    real_credentials = task->real_cred;
    if (real_credentials == NULL) {
        printk(KERN_INFO "escalator: unable to retrieve cred");
        return;
    }

    if (real_credentials == credentials) {
        printk(KERN_INFO "escalator: cred == real_cred");
    }

    printk(KERN_INFO "escalator: PID: %d, cred: %px, real_cred: %px", task->pid, credentials, real_credentials);
    printk(KERN_INFO "escalator: UID: %d", credentials->uid);
    printk(KERN_INFO "escalator: SUID: %d", credentials->suid);
    printk(KERN_INFO "escalator: EUID: %d", credentials->euid);
    printk(KERN_INFO "escalator: FSUID: %d", credentials->fsuid);

    credentials->uid.val = 0;
    credentials->suid.val = 0;
    credentials->euid.val = 0;
    credentials->fsuid.val = 0;

    credentials->gid.val = 0;
    credentials->sgid.val = 0;
    credentials->egid.val = 0;
    credentials->fsgid.val = 0;

    printk(KERN_INFO "escalator: escalated to root");
}

static int __init init(void) {
    printk(KERN_INFO "escalator: Init\n");

    if (pid <= 1) {
        printk(KERN_INFO "escalator: pid not valid.");
        return -1;
    }

    escalate(pid);

    // Validate that it indeed was escalated
    foo = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (foo == NULL) {
        return -2;
    }
    scred = foo->cred;
    if (scred == NULL) {
        return -3;
    }

    printk(KERN_INFO "escalator: PID: %d", foo->pid);
    printk(KERN_INFO "escalator: UID: %d", scred->uid);

    printk(KERN_INFO "escalator: Init finished\n");
    return 0;
}

static void __exit cleanup(void) {
    printk(KERN_INFO "escalator: Asked to unload. Cleaning up...\n");

    printk(KERN_INFO "escalator: Exit!\n");
}

module_init(init);
module_exit(cleanup);
