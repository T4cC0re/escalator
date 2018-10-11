#ifndef ESCALATOR_ESCALATE_H
#define ESCALATOR_ESCALATE_H

#include <linux/sched.h>          // Header for task_struct
#include <linux/cred.h>           // Header for cred

const struct task_struct* task;
struct cred* credentials;
struct cred* real_credentials;

static void escalate(int pid);
static void patch_credentials(struct cred* credentials);

#endif //ESCALATOR_ESCALATE_H
