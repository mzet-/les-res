
### Overview

**Protection mechanism:** Hardened user copy support (aka `HARDENED_USERCOPY`)

Available from kernel version: `4.8`

Feature can be set at compile time via `CONFIG_HARDENED_USERCOPY` config.

Excerpt from `security/Kconfig`:

```
config HARDENED_USERCOPY
    bool "Harden memory copies between kernel and userspace"
    depends on HAVE_HARDENED_USERCOPY_ALLOCATOR
    select BUG
    imply STRICT_DEVMEM
    help
      This option checks for obviously wrong memory regions when
      copying memory to/from the kernel (via copy_to_user() and
      copy_from_user() functions) by rejecting memory ranges that
      are larger than the specified heap object, span multiple
      separately allocated pages, are not on the process stack,
      or are part of the kernel text. This kills entire classes
      of heap overflow exploits and similar kernel memory exposures.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
