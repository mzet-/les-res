
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

### References

* [Control register - Wikipedia](https://en.wikipedia.org/wiki/Control_register#SMEP)
* [Supervisor Mode Execution Protection](https://web.archive.org/web/20160803075007/https://www.ncsi.com/nsatc11/presentations/wednesday/emerging_technologies/fischer.pdf)
* [Intel CPU security features · huku-/research Wiki · GitHub](https://github.com/huku-/research/wiki/Intel-CPU-security-features)
* [Intel® 64 and IA-32 Architectures Developer's Manual: Vol. 3A](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html)
* [Introduction to Processor Hardware Security Features in x86 & ARM Architectures](https://hypervsir.blogspot.com/2014/10/introduction-on-hardware-security.html)
* [SMEP: What is It, and How to Beat It on Linux](http://vulnfactory.org/blog/2011/06/05/smep-what-is-it-and-how-to-beat-it-on-linux/)
* [US20150199198A1 - Supervisor mode execution protection - Google Patents](https://patents.google.com/patent/US20150199198A1/en)
