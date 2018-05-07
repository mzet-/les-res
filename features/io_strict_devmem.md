
### Overview

**Protection mechanism:** Restrict /dev/mem access (aka `IO_STRICT_DEVMEM`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_IO_STRICT_DEVMEM` config.

Excerpt from `lib/Kconfig.debug`:

```
config IO_STRICT_DEVMEM
    bool "Filter I/O access to /dev/mem"
    depends on STRICT_DEVMEM
    ---help---
      If this option is disabled, you allow userspace (root) access to all
      io-memory regardless of whether a driver is actively using that
      range.  Accidental access to this is obviously disastrous, but
      specific access can be used by people debugging kernel drivers.

      If this option is switched on, the /dev/mem file only allows
      userspace access to *idle* io-memory ranges (see /proc/iomem) This
      may break traditional users of /dev/mem (dosemu, legacy X, etc...)
      if the driver using a given range cannot be disabled.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
