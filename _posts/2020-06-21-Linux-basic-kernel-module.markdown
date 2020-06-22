---
layout: post
title: "👶 Linux basic kernel module"
date: 2020-06-21 12:57:45 +0300
categories: driver
---

# Hi, developer

This it an article about how to write a basic `hello_world` linux module for 4.19 kernel.

# Environment

I use Gentoo Linux on Intel Celeron machine:

```
uname -a
Linux gentoo 4.19.97-gentoo #5 SMP Tue Mar 31 19:57:47 -00 2020 x86_64 Intel(R) Celeron(R) CPU N2830 @ 2.16GHz GenuineIntel GNU/Linux
```

Of course you need kernel sources! On Gentoo they are at */usr/src/linux*, on other systems you should install them via package manager or via [git](https://github.com/torvalds/linux). Google will help you!


# Code

You can browse the sources also [here](https://github.com/mrexox/mrexox.github.io/tree/hello-world-linux-module)

**hello-world.c**

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL"); /* MODULE_LICENSE is a required macro */

static int hello_init(void)
{
  /* This will print to tty0 and /var/log/kern.log */
  printk(KERN_ALERT "Hello, world!\n");
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, man!\n");
}

/*
 * Every module has its initialize and exit function.
 * This is how they are registered.
 */
module_init(hello_init);
module_exit(hello_exit);
```

**Makefile**

```makefile
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(CURDIR) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers modules.order
```

**Kbuild**

```makefile
obj-m += hello-world.o
```

# Explanation

## Writing C file

Every Linux kernel module must have following things:

- License
- Intitialization function
- Exit function

### License

`MODULE_LICENSE` is used to declare the license. These values can be used for my kernel version:

- `"GPL"`
- `"GPL v2"`
- `"GPL and additional rights"`
- `"Dual BSD/GPL"`
- `"Dual MIT/GPL"`
- `"Dual MPL/GPL"`
- `"Proprietary"`

For more information see [include/linux/module.h](https://github.com/torvalds/linux/blob/master/include/linux/module.h) file.

### Initialization

`module_init` is a macro that declares initialization function (for our case it is `hello_init`). This function is called when the module is inserted to a kernelspace. e.g. on running `insmod` command.

### Exiting

`module_exit` is a macro that declares exiting function (`hello_exit`). This function is called when the module is removed from the kernelspace. e.g. on running `rmmod` command.

## Writing Makefile

For this simple purpose (as we do not have any dependencies) we just need to run `make module` in kernel sources with ENV var `M` set on current working directory. The only thing that I notices while trying to port [ldd3 examples](https://github.com/martinezjavier/ldd3) was: you should add `obj-m += ...` statement to **Kbuild** file, not to Makefile :warning: Without this I got an error:

```
$ make
make -C /lib/modules/4.19.97-gentoo/build M=/home/ian/src/linux-modules/hello-world modules
make[1]: Entering directory '/usr/src/linux-4.19.97-gentoo'
  CC [M]  /home/ian/src/linux-modules/hello-world/hello-world.o
  Building modules, stage 2.
  MODPOST 1 modules
WARNING: modpost: missing MODULE_LICENSE() in /home/ian/src/linux-modules/hello-world/hello-world.o
see include/linux/module.h for more information
  CC      /home/ian/src/linux-modules/hello-world/hello-world.mod.o
  LD [M]  /home/ian/src/linux-modules/hello-world/hello-world.ko
make[1]: Leaving directory '/usr/src/linux-4.19.97-gentoo'
```

See this warning? Module does not work properly when compiled with this warning. Moving `obj-m += ...` to **Kbuild** helped to solve that.

## Running module

To run the module and make sure it runs, you need to do the following:

1. Insert the module (as root)
1. Watch the message on `dmesg` or tail **/var/log/kern.log** file
1. List modes, notice it runs
1. Remove the module (as root)
1. Watch the message again!

```
# insmod hello-world.ko
$ lsmod | grep hello_world # notice! dashes changed to undescrores here
hello_world            16384  0
$ tail -1 /var/log/kern.log
Jun 21 14:07:53 gentoo kernel: [10063.468659] Hello, world!
# rmmod hello_world
$ tail -1 /var/log/kern.log
Jun 21 14:10:14 gentoo kernel: [10202.723209] Goodbye, man!
```

Here we go! Hello world module is done.

## Here is the list of useful links:

- [GitHub: LDD3 examples](https://github.com/martinezjavier/ldd3) (of course you know what ldd mean!)
- [GitHub: Linux repository](https://github.com/torvalds/linux)
- [YouTube: How Linux Kernel Drivers Work](https://www.youtube.com/watch?v=juGNPLdjLH4)
- [Hello World tutorial 1](https://tldp.org/LDP/lkmpg/2.6/html/x121.html)
- [Hello World tutorial 2](https://blog.sourcerer.io/writing-a-simple-linux-kernel-module-d9dc3762c234)
- [Hello World tutorial 3](https://www.geeksforgeeks.org/linux-kernel-module-programming-hello-world-program/)
