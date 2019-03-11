
### Kernel debugging

Prepare working directory - all steps presented below will be performed inside this directory - for example:

    mkdir ~/KERNEL_HACKING; cd ~/KERNEL_HACKING

Let's use latest mainline kernel:

	git clone https://github.com/torvalds/linux

As an example we will build and debug minimal kernel module named `debugme` available at `https://github.com/mzet-/les-res/drills/debugme-module.c`:

```
git clone https://github.com/mzet-/les-res
```

Compile the kernel, for simplicity we will stick with default kernel configuration `x86_64_defconfig` with minimal modification necessary for nice debugging experience:

```
cd linux
make mrproper
make x86_64_defconfig
cat <<EOF >.config-fragment
CONFIG_DEBUG_INFO=y
CONFIG_GDB_SCRIPTS=y
EOF
./scripts/kconfig/merge_config.sh .config .config-fragment
make -j 4
```

Now, let's install default modules to the custom location (that will allow us more easily build `debugme` module against built kernel):

```
make INSTALL_MOD_PATH=~/KERNEL-HACKING/modules modules_install
```

After operations performed so far our working directory (`~/KERNEL_HACKING`) should contain:

```
linux  les-res  modules
```

Let's build example kernel module (`debugme`) against our kernel (we're providing custom `MODULE_NAME` variable to tell make what module we actually want to build, see the `Makefile` in `les-res/dirlls/` for details):

```
cd les-res/drills/
make -C ~/KERNEL-HACKING/modules/lib/modules/5.0.0+/build M=`pwd` modules MODULE_NAME=debugme
```

To be able to conveniently debug the kernel we will install QEMU:

```
Debian/Ubuntu:
sudo apt-get install qemu-system-x86

Arch:
sudo pacman -S qemu
```

Now to actually boot our custom built kernel we will need image with the filesystem, for this we will reuse `create-image.sh` script created by `https://github.com/google/syzkaller` project:

```
sudo apt-get install debootstrap
wget https://raw.githubusercontent.com/google/syzkaller/master/tools/create-image.sh -O create-image.sh
chown +x create-image.sh; ./create-image.sh --distribution wheezy
# optionally add non-default packages to the image:
sudo chroot wheezy /bin/bash -c "apt-get update; apt-get install -y curl tar time strace gcc make sysbench git vim screen usbutils"
```

Above should create `wheezy.img` file (wheezy Debian image) and ssh keys for accessing the system (after booting it).

Let's boot it (we're turning off `KASLR` with `nokaslr` kernel boot parameter):

```
sudo qemu-system-x86_64 -s  -kernel linux/arch/x86/boot/bzImage   -append "console=ttyS0 nokaslr root=/dev/sda debug earlyprintk=serial"  -hda wheezy.img   -net user,hostfwd=tcp::10021-:22 -net nic   -enable-kvm   -nographic   -m 2G   -smp 2   -pidfile vm.pid   2>&1 | tee vm.log

# you can kill the guest by running:
sudo sh -c 'kill $(cat vm.pid)'
```

Now we should have our guest system under QEMU with our custom built kernel up and running. Let's copy and load our kernel module for debugging onto the (guest) system:

```
scp -i ssh/id_rsa -P 10021 -o "StrictHostKeyChecking no" les-res/drills/debugme-module.ko root@localhost:
ssh -i ssh/id_rsa -p 10021 -o "StrictHostKeyChecking no" root@localhost "insmod /root/debugme-module.ko; lsmod"
```

Finally, we're ready to start our remote debugging session:

```
$ cd linux
$ gdb vmlinux
(gdb) target remote :1234
# load debug symbols for the kernel and for 'debugme-module.ko' module
(gdb) lx-symbols
(gdb) lx-symbols ../les-res/drills/
# set breakpoint 'debugme_func' from 'debugme-module.ko' module:
(gdb) break debugme_func
(gdb) continue
```

Trigger call to 'debugme_func' function:

```
ssh -i ssh/id_rsa -p 10021 -o "StrictHostKeyChecking no" root@localhost "cat /proc/debugme"
```

Enjoy your kernel debugging session.
