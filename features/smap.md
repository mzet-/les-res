
### Overview

**Protection mechanism:** Supervisor Mode Access Prevention (SMAP) support

Available from kernel version: `3.7`

For kernels `3.7+` SMAP support is turned on by default if underlying CPU supports it.

To verify if SMAP is turned on, one can run: `grep -i smap /proc/cpuinfo`.

Excerpt from [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://software.intel.com/en-us/articles/intel-sdm):

```
TBD (Volume 3A, 4-3, Paragraph 4.1.3)
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD

### References

* [Control register - Wikipedia](https://en.wikipedia.org/wiki/Control_register)
* [Supervisor Mode Access Prevention - Wikipedia](https://en.wikipedia.org/wiki/Supervisor_Mode_Access_Prevention)
* [x86: Supervisor Mode Access Prevention [LWN.net]](https://lwn.net/Articles/517251/)
* [Intel CPU security features · huku-/research Wiki · GitHub](https://github.com/huku-/research/wiki/Intel-CPU-security-features)
* [Intel® 64 and IA-32 Architectures Developer's Manual: Vol. 3A](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html)
* [Introduction to Processor Hardware Security Features in x86 & ARM Architectures](https://hypervsir.blogspot.com/2014/10/introduction-on-hardware-security.html)
