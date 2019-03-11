#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

struct proc_dir_entry *e;

static ssize_t debugme_func(struct file * f, char __user * buf, size_t len, loff_t * offset) {
   int n = 4;
   printk("step 1\n");
   printk("step 2\n");
   printk("step 3\n");

   return n + 3;
}

int debugme_open(struct inode *in_node, struct file *filp)
{
        printk(KERN_INFO "debugme file was opened\n");
        return 0;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open  = debugme_open,
    .read  = debugme_func
};

static int __init init_debugme_mod(void) {
   printk("module loaded\n");
    
   e = proc_create("debugme", 0666, 0, &fops);

   return 0;
}

static void __exit fini_debugme_mod(void) {
   remove_proc_entry("debugme", NULL);
   printk("module unloaded\n");
}

module_init(init_debugme_mod);
module_exit(fini_debugme_mod);
