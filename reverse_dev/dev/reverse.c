#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "reverse"
#define BUF_LEN 100

static int major;

enum {
    CDEV_NOT_USED = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};

static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);
static char msg[BUF_LEN];
static char* cur_pos = msg;
static struct class *cls;

static struct file_operations reverse_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

static int __init reverse_init(void) { 
    major = register_chrdev(0, DEVICE_NAME, &reverse_fops);

    if (major < 0) {
        pr_alert("Registering reverse device failed with %d\n", major);
        return major;
    }

    pr_info("I was assigned major number %d.\n", major);

    cls = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("Device created on /dev/%s\n", DEVICE_NAME);

    return SUCCESS;
}

static void __exit reverse_exit(void) { 
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, DEVICE_NAME);
}

static int device_open(struct inode *inode, struct file *file) {
    if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN)) {
        return -EBUSY;
    }

    cur_pos = msg;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
    atomic_set(&already_open, CDEV_NOT_USED);
    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read(struct file *filp, char __user *buff, size_t length, loff_t *offset) {
    int bytes_read = 0;
    while (length > 0 && cur_pos > msg) {
        *buff = *(cur_pos - 1);
        buff++;
        cur_pos--;
        length--;
        bytes_read++;
    }

    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char __user *buff, size_t length, loff_t *off) {
    ssize_t written = 0;
    while (length > 0 && (cur_pos - msg) / sizeof(cur_pos) < BUF_LEN) {
        *cur_pos = *buff;
        length--;
        cur_pos++;
        buff++;
        written++;
    }

    return written;
}

module_init(reverse_init);
module_exit(reverse_exit);

MODULE_LICENSE("GPL");

