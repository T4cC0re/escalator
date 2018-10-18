#ifndef ESCALATOR_DRIVER_H
#define ESCALATOR_DRIVER_H

#include <linux/device.h>  // Header to support the kernel Driver Model
#include <linux/fs.h>      // Header for the Linux file system support
#include <linux/uaccess.h> // Required for the copy_to_user function
#include<linux/sysfs.h>
#include<linux/kobject.h>

#define DEVICE_NAME "escalator"       // Appear as /dev/<DEVICE_NAME>
#define CLASS_NAME  "escalator"       // Appear as /sys/class/<CLASS_NAME>
#define SYSFS_ATTR   escalate_process // Appear as /sys/kernel/<SYSFS_ATTR> - DO NOT QUOTE!

static int majorNumber;                 // For MKDEV, registered via register_chrdev and DEVICE_NAME
static struct class* devClass  = NULL; // Device class
static struct device* dev = NULL;       // Actual device
struct kobject *kobj_ref;

// sysfs
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count);
struct kobj_attribute SYSFS_ATTR = __ATTR(SYSFS_ATTR, 0600, sysfs_show, sysfs_store);

// Implemented fs operations
static struct file_operations fops = {
    .owner = THIS_MODULE,
};

// init & cleanup
static int escalator_driver_init(void);
static void escalator_driver_cleanup(void);

#endif //ESCALATOR_DRIVER_H
