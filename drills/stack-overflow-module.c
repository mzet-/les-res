#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/cred.h>

MODULE_LICENSE("GPL v2");

struct proc_dir_entry *e;

static ssize_t stackoverflow_func(struct file *f, const char __user *user_buf, size_t len, loff_t *offset) {

    char buf[16];
    memcpy(buf, user_buf, len);

    return len;
}

int stackoverflow_open(struct inode *in_node, struct file *filp)
{
    printk(KERN_INFO "stackoverflow file was opened\n");
    return 0;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open  = stackoverflow_open,
    .write = stackoverflow_func
};

static int __init init_stackoverflow_mod(void) {
    printk("module loaded\n");
    
    e = proc_create("stackoverflow", 0666, 0, &fops);

    return 0;
}

static void __exit fini_stackoverflow_mod(void) {
    remove_proc_entry("stackoverflow", NULL);
    printk("module unloaded\n");
}

module_init(init_stackoverflow_mod);
module_exit(fini_stackoverflow_mod);
