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
