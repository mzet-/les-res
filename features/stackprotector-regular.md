
### Overview

**Protection mechanism:** GCC stack protector support (aka CONFIG_STACKPROTECTOR)

Available from kernel version: `2.6.19`

Feature can be set at compile time via:

- `CONFIG_STACKPROTECTOR=y` config
- `CONFIG_CC_STACKPROTECTOR=y` config (before `v4.18`)

Excerpt from `arch/Kconfig`:

```
config STACKPROTECTOR
	bool "Stack Protector buffer overflow detection"
	depends on HAVE_STACKPROTECTOR
	depends on $(cc-option,-fstack-protector)
	default y
	help
	  This option turns on the "stack-protector" GCC feature. This
	  feature puts, at the beginning of functions, a canary value on
	  the stack just before the return address, and validates
	  the value just before actually returning.  Stack based buffer
	  overflows (that need to overwrite this return address) now also
	  overwrite the canary, which gets detected and the attack is then
	  neutralized via a kernel panic.

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
