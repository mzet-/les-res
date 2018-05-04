
### Overview

**Protection mechanism:** GCC stack protector STRONG support (aka CC_STACKPROTECTOR_STRONG)

Available from kernel version: `TBD`

Feature can be set at compile time via `CONFIG_CC_STACKPROTECTOR_STRONG` config.

Excerpt from `arch/Kconfig`:

```
config CC_STACKPROTECTOR_STRONG
	bool "Strong"
	help
	  Functions will have the stack-protector canary logic added in any
	  of the following conditions:

	  - local variable's address used as part of the right hand side of an
	    assignment or function argument
	  - local variable is an array (or union containing an array),
	    regardless of array type or length
	  - uses register local variables

	  This feature requires gcc version 4.9 or above, or a distribution
	  gcc with the feature backported ("-fstack-protector-strong").

	  On an x86 "defconfig" build, this feature adds canary checks to
	  about 20% of all kernel functions, which increases the kernel code
	  size by about 2%.
```

### Protection mechanism analysis

TBD

### Associated vulnerabilities

TBD
