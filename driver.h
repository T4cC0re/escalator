#ifndef ESCALATOR_DRIVER_H
#define ESCALATOR_DRIVER_H

#include <linux/device.h>  // Header to support the kernel Driver Model
#include <linux/fs.h>      // Header for the Linux file system support
#include <linux/uaccess.h> // Required for the copy_to_user function

#define  DEVICE_NAME "escalator" // Appear as /dev/<DEVICE_NAME>
#define  CLASS_NAME  "escalator" // Appear as /sys/class/<CLASS_NAME>

static int majorNumber;                 // For MKDEV, registered via register_chrdev and DEVICE_NAME
static struct class* devClass  = NULL; // Device class
static struct device* dev = NULL;       // Actual device

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

// Implemented fs operations
static struct file_operations fops =
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
    .owner = THIS_MODULE,
};

// init & cleanup
static int escalator_driver_init(void);
static void escalator_driver_cleanup(void);

#endif //ESCALATOR_DRIVER_H
