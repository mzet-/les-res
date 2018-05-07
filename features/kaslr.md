
### Overview

**Protection mechanism:** Randomize the address of the kernel image (KASLR)

Available from kernel version: `4.7`

Feature can be set at compile time via `CONFIG_RANDOMIZE_BASE` config. Can be truned off at boot time using `nokaslr` kernel boot parameter. 

Excerpt from `arch/x86/Kconfig`:

```
config RANDOMIZE_BASE
    bool "Randomize the address of the kernel image (KASLR)"
    depends on RELOCATABLE
    default y
    ---help---
      In support of Kernel Address Space Layout Randomization (KASLR),
      this randomizes the physical address at which the kernel image
      is decompressed and the virtual address where the kernel
      image is mapped, as a security feature that deters exploit
      attempts relying on knowledge of the location of kernel
      code internals.

      On 64-bit, the kernel physical and virtual addresses are
      randomized separately. The physical address will be anywhere
      between 16MB and the top of physical memory (up to 64TB). The
      virtual address will be randomized from 16MB up to 1GB (9 bits
      of entropy). Note that this also reduces the memory space
      available to kernel modules from 1.5GB to 1GB.

      On 32-bit, the kernel physical and virtual addresses are
      randomized together. They will be randomized from 16MB up to
      512MB (8 bits of entropy).

      Entropy is generated using the RDRAND instruction if it is
      supported. If RDTSC is supported, its value is mixed into
      the entropy pool as well. If neither RDRAND nor RDTSC are
      supported, then entropy is read from the i8254 timer. The
      usable entropy is limited by the kernel being built using
      2GB addressing, and that PHYSICAL_ALIGN must be at a
      minimum of 2MB. As a result, only 10 bits of entropy are
      theoretically possible, but the implementations are further
      limited due to memory layouts.
```

Excerpt from `Documentation/admin-guide/kernel-parameters.txt`:

```
nokaslr     [KNL]
            When CONFIG_RANDOMIZE_BASE is set, this disables
            kernel and module base offset ASLR (Address Space
            Layout Randomization).
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
