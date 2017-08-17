#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL");

static char *name = "jaycee";
static int times = 1;
module_param(times, int, 0);
module_param(name, charp, S_IRUGO);

static int hello_init(void)
{
    int i;
    for(i = 0; i < times; i++){
        printk(KERN_ALERT "hello, world, %s\n", name);
    }
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("print hello world");
