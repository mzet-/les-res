
### Overview

**Protection mechanism:** Credential management struct validation.

Available from kernel version: `2.6.32`

Feature can be set at compile time via `CONFIG_DEBUG_CREDENTIALS` config. Requires `CONFIG_DEBUG_KERNEL`.

Excerpt from `lib/Kconfig.debug`:

```
config DEBUG_CREDENTIALS
	bool "Debug credential management"
	depends on DEBUG_KERNEL
	help
	  Enable this to turn on some debug checking for credential
	  management.  The additional code keeps track of the number of
	  pointers from task_structs to any given cred struct, and checks to
	  see that this number never exceeds the usage count of the cred
	  struct.

	  Furthermore, if SELinux is enabled, this also checks that the
	  security pointer in the cred struct is never seen to be invalid.
```

### Protection mechanism analysis

* https://lwn.net/Articles/350208/
* https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?h=v4.8&id=e0e817392b9acf2c98d3be80c233dddb1b52003d
* https://zatoichi-engineer.github.io/2017/11/13/kernel-structure-validation.html

### Associated vulnerabilities

TBD
