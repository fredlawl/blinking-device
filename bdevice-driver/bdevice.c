#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "bdevice.h"

static int __init bdevice_init(void)
{
	bdevice_info("Module installed");
	return 0;
}
module_init(bdevice_init);

static void __exit bdevice_exit(void)
{
	bdevice_info("Module removed");
}
module_exit(bdevice_exit);

MODULE_AUTHOR("Frederick Lawler <fred@fredlawl.com>");
MODULE_DESCRIPTION("Kernel serial interface for bdevice.");
MODULE_LICENSE("GPL v2");
