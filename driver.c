#include "driver.h"

static int escalator_driver_init() {
    printk(KERN_INFO "escalator: Initializing escalator driver...\n");

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber<0){
        printk(KERN_ALERT "escalator failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "escalator: registered correctly with major number %d\n", majorNumber);

    devClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(devClass)){                // Check for error and clean up if there is
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(devClass);          // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "escalator: device class registered correctly\n");

    dev = device_create(devClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(dev)){               // Clean up if there is an error
        class_destroy(devClass);           // Repeated code but the alternative is goto statements
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(dev);
    }
    printk(KERN_INFO "escalator: device class created correctly\n"); // Made it! device was initialized
    return 0;
}

static void escalator_driver_cleanup() {
    printk(KERN_INFO "escalator: Cleaning up escalator driver...\n");
    device_destroy(devClass, MKDEV(majorNumber, 0));
    class_unregister(devClass);
    class_destroy(devClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "escalator: Cleanup complete...\n");
}

static int dev_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "escalator: Device has been opened \n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "escalator: Sent characters to the user\n");
    return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
    printk(KERN_INFO "escalator: Received characters from the user\n");
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "escalator: Device successfully closed\n");
    return 0;
}
