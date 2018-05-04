
### Overview

**Protection mechanism:** Supervisor Mode Execution Protection (SMEP) support

Available from kernel version: `3.0`

For kernels `3.0+` SMEP support is turned on by default if underlying CPU supports it.

To verify if SMEP is turned on, one can run: `grep -i smep /proc/cpuinfo`.

Excerpt from [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://software.intel.com/en-us/articles/intel-sdm):

```
TBD (Volume 3A, 4-3, Paragraph 4.1.3)
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
