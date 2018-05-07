
### Overview

**Protection mechanism:** Restrict /dev/mem access (aka `STRICT_DEVMEM`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_STRICT_DEVMEM` config.

Excerpt from `lib/Kconfig.debug`:

```
config STRICT_DEVMEM
    bool "Filter access to /dev/mem"
    depends on MMU && DEVMEM
    depends on ARCH_HAS_DEVMEM_IS_ALLOWED
    default y if PPC || X86 || ARM64
    ---help---
      If this option is disabled, you allow userspace (root) access to all
      of memory, including kernel and userspace memory. Accidental
      access to this is obviously disastrous, but specific access can
      be used by people debugging the kernel. Note that with PAT support
      enabled, even in this case there are restrictions on /dev/mem
      use due to the cache aliasing requirements.

      If this option is switched on, and IO_STRICT_DEVMEM=n, the /dev/mem
      file only allows userspace access to PCI space and the BIOS code and
      data regions.  This is sufficient for dosemu and X and all common
      users of /dev/mem.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
