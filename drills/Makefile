ccflags-y += -g -DDEBUG -O0
obj-m := ${MODULE_NAME}-module.o

# disable canary stack protection for 'stack-overflow-module.c':
ifeq ($(MODULE_NAME),stack-overflow)
    ccflags-y += -fno-stack-protector
endif

clean:
	rm -f .*.cmd
	rm -f *.o
	rm -f *.ko
	rm -f *.order
	rm -f *.symvers
	rm -f *.mod.c
	rm -rf .tmp_versions
	
