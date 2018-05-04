
### Overview

**Protection mechanism:** GCC stack protector support (aka CC_STACKPROTECTOR_REGULAR)

Available from kernel version: `TBD`

Feature can be set at compile time via `CC_STACKPROTECTOR_REGULAR` config.

Excerpt from `arch/Kconfig`:

```
config CC_STACKPROTECTOR_REGULAR
	bool "Regular"
	help
	  Functions will have the stack-protector canary logic added if they
	  have an 8-byte or larger character array on the stack.

	  This feature requires gcc version 4.2 or above, or a distribution
	  gcc with the feature backported ("-fstack-protector").

	  On an x86 "defconfig" build, this feature adds canary checks to
	  about 3% of all kernel functions, which increases kernel code size
	  by about 0.3%.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
