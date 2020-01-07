#define LOG_PREFIX "bdevice: "

#define bdevice_printk(level, fmt, arg...)	\
	printk(level LOG_PREFIX fmt "\n", ##arg)

#define bdevice_info(fmt, arg...)	\
	printk(KERN_INFO LOG_PREFIX fmt "\n", ##arg)

#define bdevice_err(fmt, arg...)	\
	printk(KERN_ERR LOG_PREFIX fmt "\n", ##arg)
