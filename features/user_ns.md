
### Overview

**Attack surface:** User namespaces for unprivileged accounts (aka `USER_NS`)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_USER_NS` config.

Excerpt from `init/Kconfig`:

```
config USER_NS
    bool "User namespace"
    default n
    help
      This allows containers, i.e. vservers, to use user namespaces
      to provide different user info for different servers.

      When user namespaces are enabled in the kernel it is
      recommended that the MEMCG option also be enabled and that
      user-space use the memory control groups to limit the amount
      of memory a memory unprivileged users can use.
```

### Attack surface analysis

TBD

### Associated vulnerabilities

TBD
