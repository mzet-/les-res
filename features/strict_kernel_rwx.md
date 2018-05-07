
### Overview

**Protection mechanism:** Make kernel text and rodata read-only (aka `STRICT_KERNEL_RWX`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_STRICT_KERNEL_RWX` config.

Excerpt from `arch/Kconfig`:

```
config STRICT_KERNEL_RWX
    bool "Make kernel text and rodata read-only" if ARCH_OPTIONAL_KERNEL_RWX
    depends on ARCH_HAS_STRICT_KERNEL_RWX
    default !ARCH_OPTIONAL_KERNEL_RWX || ARCH_OPTIONAL_KERNEL_RWX_DEFAULT
    help
      If this is set, kernel text and rodata memory will be made read-only,
      and non-text memory will be made non-executable. This provides
      protection against certain security exploits (e.g. executing the heap
      or modifying text)

      These features are considered standard security practice these days.
      You should say Y here in almost all cases.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
