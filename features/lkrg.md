### Overview

**Protection mechanism:** Linux Kernel Runtime Guard (LKRG) kernel module

Excerpt from [LKRG homepage](https://www.openwall.com/lkrg/):

> Linux Kernel Runtime Guard (LKRG) is a loadable kernel module that performs runtime integrity checking of the Linux kernel and detection of security vulnerability exploits against the kernel.

To verify if LKRG is installed, one can run: `lsmod | grep lkrg`

However, LKRG can be hidden using the `lkrg.hide=1` sysctl parameter.

In the event that LKRG is hidden, it's still possible to detect the module by checking for the presence of the associated sysctl parameters with: `test -d /proc/sys/lkrg && echo true`.

For more information, see: [LKRG [Openwall Community Wiki]](https://openwall.info/wiki/p_lkrg/Main)

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
