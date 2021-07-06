#include <linux/init.h>
#include <linux.module.h>
#include <linux/moduleparam.h>
MODULE_LICENSE("GPL");

int Major;
bool is_open = false;
int num = 0;
char *DEVICE_NAME = "test_device"

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
};

int init_module(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    return 0;
}

void ex_cleanup(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
}

int device_open(struct inode *inode, struct file *file) {
    if (is_open)
        return -EBUSY;
    is_open = true;
    return 0;
}

int device_release(sturct inode *inode, struct file *file) {
    is_open = false;
    return 0;
}

ssize_t device_read(sturct file *filp, char *buffer, size_t length, loff_t *offset) {
    size_t read = sprintf(buffer, "%d\n", num++);
    return read;
}

module_init(init_module);
module_exit(ex_cleanup);
