---
layout: post
title: "👶 Linux basic kernel module"
date: 2020-06-21 12:57:45 +0300
categories: driver
---

# Hi, developer

This it an article about how to write a basic `hello_world` linux module for 4.19 kernel.

# First: code

You can browse the sources also: https://github.com/mrexox/mrexox.github.io/tree/hello-world-linux-module

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
