
### Overview

**Protection mechanism:** Restrict unprivileged access to kernel syslog (aka `dmesg_restrict`)

Available from kernel version: `2.6.37`

Feature can be changed at runtime via `TBD` config.

Excerpt from `Documentation/sysctl/kernel.txt`:

```
dmesg_restrict:

This toggle indicates whether unprivileged users are prevented
from using dmesg(8) to view messages from the kernel's log buffer.
When dmesg_restrict is set to (0) there are no restrictions. When
dmesg_restrict is set set to (1), users must have CAP_SYSLOG to use
dmesg(8).

The kernel config option CONFIG_SECURITY_DMESG_RESTRICT sets the
default value of dmesg_restrict.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
