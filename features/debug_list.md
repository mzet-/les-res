### Overview

**Protection mechanism:** Linked list struct validation.

Available from kernel version: `2.6.19`

Feature can be set at compile time via `CONFIG_DEBUG_LIST` config. Requires `CONFIG_DEBUG_KERNEL` or `BUG_ON_DATA_CORRUPTION`.

Excerpt from `lib/Kconfig.debug`:

```
config DEBUG_LIST
	bool "Debug linked list manipulation"
	depends on DEBUG_KERNEL || BUG_ON_DATA_CORRUPTION
	help
	  Enable this to turn on extended checks in the linked-list
walking routines.
```

### Protection mechanism analysis

* https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?h=v4.8&id=199a9afc3dbe98c35326f1d3907ab94dae953a6e
* https://zatoichi-engineer.github.io/2017/11/13/kernel-structure-validation.html

### Associated vulnerabilities

* https://access.redhat.com/security/cve/CVE-2017-10661
* https://twitter.com/maddiestone/status/1245834936629616640
