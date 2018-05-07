
### Overview

**Attack surface:** Support for /dev/kmem access (aka `DEVKMEM`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_DEVKMEM=y` config.

Excerpt from `man 4 kmem`:

```
DESCRIPTION
       mem  is  a character device file that is an image of the main memory of
       the computer.  It may be used, for example, to examine (and even patch)
       the system.

       Byte  addresses  in  mem  are interpreted as physical memory addresses.
       References to nonexistent locations cause errors to be returned.

       Examining and patching is likely to lead  to  unexpected  results  when
       read-only or write-only bits are present.

       It is typically created by:

              mknod -m 660 /dev/mem c 1 1
              chown root:kmem /dev/mem

       The file kmem is the same as mem, except that the kernel virtual memory
       rather than physical memory is accessed.

       It is typically created by:

              mknod -m 640 /dev/kmem c 1 2
              chown root:kmem /dev/kmem
```

### Attack surface analysis

TBD

### Associated vulnerabilities

TBD
