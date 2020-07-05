### Overview

**Protection mechanism:** Notifier call chain validation.

Available from kernel version: `2.6.29`

Feature can be set at compile time via `CONFIG_DEBUG_NOTIFIERS` config. Requires `CONFIG_DEBUG_KERNEL`.

Excerpt from `lib/Kconfig.debug`:

```
config DEBUG_NOTIFIERS
	bool "Debug notifier call chains"
	depends on DEBUG_KERNEL
	help
	  Enable this to turn on sanity checking for notifier call chains.
	  This is most useful for kernel developers to make sure that
	  modules properly unregister themselves from notifier chains.
	  This is a relatively cheap check but if you care about maximum
	  performance, say N.
```

### Protection mechanism analysis

* https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?h=v4.8&id=1b2439dbb703ae8d95a9ce7ece6b7800b80f41f0
* https://zatoichi-engineer.github.io/2017/11/13/kernel-structure-validation.html

### Associated vulnerabilities

TBD
