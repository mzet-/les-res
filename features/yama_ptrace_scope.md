### Overview

**Protection mechanism:** Prevent users from using `ptrace` to examine the memory and state of their processes (aka `yama.ptrace_scope`)

Available from kernel version: `3.4`

Feature can be set at compile time via `CONFIG_SECURITY_YAMA` config. Can be changed after boot using `/proc/sys/kernel/yama/ptrace_scope`.

Excerpt from `Documentation/security/Yama.txt`:

```
ptrace_scope:

As Linux grows in popularity, it will become a larger target for
malware. One particularly troubling weakness of the Linux process
interfaces is that a single user is able to examine the memory and
running state of any of their processes. For example, if one application
(e.g. Pidgin) was compromised, it would be possible for an attacker to
attach to other running processes (e.g. Firefox, SSH sessions, GPG agent,
etc) to extract additional credentials and continue to expand the scope
of their attack without resorting to user-assisted phishing.

[...]

The sysctl settings (writable only with CAP_SYS_PTRACE) are:

0 - classic ptrace permissions: a process can PTRACE_ATTACH to any other
    process running under the same uid, as long as it is dumpable (i.e.
    did not transition uids, start privileged, or have called
    prctl(PR_SET_DUMPABLE...) already). Similarly, PTRACE_TRACEME is
    unchanged.

1 - restricted ptrace: a process must have a predefined relationship
    with the inferior it wants to call PTRACE_ATTACH on. By default,
    this relationship is that of only its descendants when the above
    classic criteria is also met. To change the relationship, an
    inferior can call prctl(PR_SET_PTRACER, debugger, ...) to declare
    an allowed debugger PID to call PTRACE_ATTACH on the inferior.
    Using PTRACE_TRACEME is unchanged.

2 - admin-only attach: only processes with CAP_SYS_PTRACE may use ptrace
    with PTRACE_ATTACH, or through children calling PTRACE_TRACEME.

3 - no attach: no processes may use ptrace with PTRACE_ATTACH nor via
    PTRACE_TRACEME. Once set, this sysctl value cannot be changed.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

* https://github.com/nongiach/sudo_inject

### References

* https://www.kernel.org/doc/Documentation/security/Yama.txt
* http://man7.org/linux/man-pages/man2/ptrace.2.html
* https://lwn.net/Articles/393012/
* https://lwn.net/Articles/492667/
* https://linux-audit.com/protect-ptrace-processes-kernel-yama-ptrace_scope/

