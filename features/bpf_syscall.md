
### Overview

**Attack surface:** Unprivileged access to bpf() system call (aka `BPF_SYSCALL`)

Available from kernel version: `3.18`

Feature can be set at compile time via `CONFIG_BPF_SYSCALL` config.

Excerpt from `init/Kconfig`:

```
config BPF_SYSCALL
    bool "Enable bpf() system call"
    select ANON_INODES
    select BPF
    default n
    help
      Enable the bpf() system call that allows to manipulate eBPF
      programs and maps via file descriptors.
```

### Attack surface analysis

TBD

### Associated vulnerabilities

TBD
