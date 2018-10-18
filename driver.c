#include "driver.h"
#include "escalate.c"

static int escalator_driver_init() {
    int sysfsError = 0;

    printk(KERN_INFO "escalator: Initializing escalator driver...\n");

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0){
        printk(KERN_ALERT "escalator failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "escalator: registered correctly with major number %d\n", majorNumber);

    devClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(devClass)){
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "escalator: Failed to register device class\n");
        return PTR_ERR(devClass);
    }
    printk(KERN_INFO "escalator: device class registered correctly\n");

    dev = device_create(devClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(dev)){
        class_destroy(devClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "escalator: Failed to create the device\n");
        return PTR_ERR(dev);
    }

    sysfsError = sysfs_create_file(kernel_kobj, &SYSFS_ATTR.attr);
    if(sysfsError < 0){
        printk(KERN_ALERT "escalator: Cannot create sysfs file\n");
        sysfs_remove_file(kernel_kobj, &SYSFS_ATTR.attr);
        device_destroy(devClass, MKDEV(majorNumber, 0));
        class_unregister(devClass);
        class_destroy(devClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        return sysfsError;
    }

    printk(KERN_INFO "escalator: device class created correctly\n"); // Made it! device was initialized
    return 0;
}

static void escalator_driver_cleanup() {
    printk(KERN_INFO "escalator: Cleaning up escalator driver...\n");
    sysfs_remove_file(kernel_kobj, &SYSFS_ATTR.attr);
    device_destroy(devClass, MKDEV(majorNumber, 0));
    class_unregister(devClass);
    class_destroy(devClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "escalator: Cleanup complete...\n");
}

static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "write pid here to escalate\n");
}

static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    int pid = 0;
    printk(KERN_INFO "escalator: Invoked via sysfs...\n");
    sscanf(buf,"%d",&pid);
    printk(KERN_INFO "escalator: parsed PID %d\n", pid);
    escalate(pid);
    return count;
}
