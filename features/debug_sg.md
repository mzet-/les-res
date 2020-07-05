### Overview

**Protection mechanism:** Scatter-gather (sg) tables validation.

Available from kernel version: `2.6.24`

Feature can be set at compile time via `CONFIG_DEBUG_SG` config. Requires `CONFIG_DEBUG_KERNEL`.

Excerpt from `lib/Kconfig.debug`:

```
config DEBUG_SG
	bool "Debug SG table operations"
	depends on DEBUG_KERNEL
	help
	  Enable this to turn on checks on scatter-gather tables. This can
	  help find problems with drivers that do not properly initialize
	  their sg tables.
```

### Protection mechanism analysis

* https://lwn.net/Articles/234617/
* https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?h=v4.8&id=d6ec084200c37683278c821338f74ddf21ab80f5
* https://zatoichi-engineer.github.io/2017/11/13/kernel-structure-validation.html

### Associated vulnerabilities

TBD
