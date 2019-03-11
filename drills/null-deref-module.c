#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>

#define NULLDEREF_IOCTL_BASE 'D'
#define TRIGGER_NULL_DEREF _IO(NULLDEREF_IOCTL_BASE, 1)

long null_deref_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int retval;
    char *kdata;

    if(cmd == TRIGGER_NULL_DEREF) {
        struct Ops {
			ssize_t (*do_it)(void);
		};
		static struct Ops *ops = NULL;

        printk(KERN_INFO "null-deref: trigerring vuln\n");

        /* [1] dereferencing NULL pointer */
		return ops->do_it();
    }
}

int null_deref_open(struct inode *in_node, struct file *filp)
{
	printk(KERN_INFO "null-deref device was opened\n");
	return 0;
}

int null_deref_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "null-deref device was closed\n");
	return 0;
}

struct file_operations null_deref_fops = {
    .owner  = THIS_MODULE,
    .open   = null_deref_open,
    .release= null_deref_release,
    .unlocked_ioctl = null_deref_ioctl,
    .compat_ioctl = null_deref_ioctl
};

static struct miscdevice null_deref_misc = {
    .minor = MISC_DYNAMIC_MINOR,
	.name = "null-deref",
	.fops = &null_deref_fops,
};

int init_module(void)
{
	int result;

	printk(KERN_INFO "null-deref module loaded\n");

	result = misc_register(&null_deref_misc);
	if (unlikely(result)) {
		printk(KERN_ERR "failed to register misc device.\n");
		return result;
	} 

	return 0;
}

void cleanup_module(void)
{
	int result;
	misc_deregister(&null_deref_misc);

	printk(KERN_INFO "null-deref module unloaded\n");
}

MODULE_LICENSE("GPL");
