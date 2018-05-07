
### Overview

**Protection mechanism:** Set loadable kernel module data as NX and text as RO (aka `STRICT_MODULE_RWX`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_STRICT_MODULE_RWX` config.

Excerpt from `arch/Kconfig`:

```
config STRICT_MODULE_RWX
    bool "Set loadable kernel module data as NX and text as RO" if ARCH_OPTIONAL_KERNEL_RWX
    depends on ARCH_HAS_STRICT_MODULE_RWX && MODULES
    default !ARCH_OPTIONAL_KERNEL_RWX || ARCH_OPTIONAL_KERNEL_RWX_DEFAULT
    help
      If this is set, module text and rodata memory will be made read-only,
      and non-text memory will be made non-executable. This provides
      protection against certain security exploits (e.g. writing to text)
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
