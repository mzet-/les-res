
### Overview

**Protection mechanism:** Prevent userland modifications to the running kernel.

Available from kernel version: `5.4`

Excerpt from `Documentation/admin-guide/kernel-parameters.txt`:

```
lockdown=	[SECURITY]
{ integrity | confidentiality }

Enable the kernel lockdown feature. If set to
integrity, kernel features that allow userland to
modify the running kernel are disabled. If set to
confidentiality, kernel features that allow userland
to extract confidential information from the kernel
are also disabled.
```

Excerpt from `security/lockdown/Kconfig`:

```
config SECURITY_LOCKDOWN_LSM
	bool "Basic module for enforcing kernel lockdown"
	depends on SECURITY
	select MODULE_SIG if MODULES
	help
	  Build support for an LSM that enforces a coarse kernel lockdown
	  behaviour.

config SECURITY_LOCKDOWN_LSM_EARLY
	bool "Enable lockdown LSM early in init"
	depends on SECURITY_LOCKDOWN_LSM
	help
	  Enable the lockdown LSM early in boot. This is necessary in order
	  to ensure that lockdown enforcement can be carried out on kernel
	  boot parameters that are otherwise parsed before the security
	  subsystem is fully initialised. If enabled, lockdown will
	  unconditionally be called before any other LSMs.

choice
	prompt "Kernel default lockdown mode"
	default LOCK_DOWN_KERNEL_FORCE_NONE
	depends on SECURITY_LOCKDOWN_LSM
	help
	  The kernel can be configured to default to differing levels of
	  lockdown.

config LOCK_DOWN_KERNEL_FORCE_NONE
	bool "None"
	help
	  No lockdown functionality is enabled by default. Lockdown may be
	  enabled via the kernel commandline or /sys/kernel/security/lockdown.

config LOCK_DOWN_KERNEL_FORCE_INTEGRITY
	bool "Integrity"
	help
	 The kernel runs in integrity mode by default. Features that allow
	 the kernel to be modified at runtime are disabled.

config LOCK_DOWN_KERNEL_FORCE_CONFIDENTIALITY
	bool "Confidentiality"
	help
	 The kernel runs in confidentiality mode by default. Features that
	 allow the kernel to be modified at runtime or that permit userland
	 code to read confidential material held inside the kernel are
	 disabled.
```

### Protection mechanism analysis

Bypasses:

* https://github.com/xairy/unlockdown

### Associated vulnerabilities

TBD
