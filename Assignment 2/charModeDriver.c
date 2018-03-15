#include "charModeDriver.h"


MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VER);


static int Major;
static int Device_Open = 0;

static char msg[BUFFER_LENGTH];
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};


static int __init init_module(void) {
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Failed to register character-mode device: %d\n", Major);
		return Major;
	}
	
	printk(KERN_INFO "Installing module.\n");
	printk(KERN_INFO "Registered character-mode device with major number: %d\n", Major);
	
	return SUCCESS;
}

static void __exit cleanup_module(void) {
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0) {
		printk(KERN_ALERT "Failed to unregister character-mode device: %d with error-code: %d\n", Major, ret);
	} else {
		printk(KERN_INFO "Unregistered character-mode device: %d\n", Major);
	}
	
	printk(KERN_INFO "Removing module.\n");
}

static int device_open(struct *inode, struct file *file) {
	static int counter = 0;
	
	if (Device_Open) {
		printk(KERN_WARNING "Attempted to open character-mode device but it is already open.\n");
		return -EBUSY;
	}
	
	Device_Open++;
	counter++;
	printk(KERN_INFO "Opened character-mode device. Opened %d time(s).\n", counter);
	
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
	if (!Device_Open) {
		printk(KERN_WARNING "Attempted to close character-mode device but it is not open.\n");
		return -EPERM;
	}
	
	Device_Open--;
	printk(KERN_INFO "Closed character-mode device.\n");

	module_put(THIS_MODULE);

	return SUCCESS;
}

static ssize_t device_read(struct file *filp, char *buffer,	size_t length, loff_t *offset) {
	int bytes_read = 0;

	if (*msg_Ptr == 0) {
		return 0;
	}

	while (length && *msg_Ptr) {
		put_user(*(msg_Ptr++), buffer++);
		
		length--;
		bytes_read++;
	}
	
	printk(KERN_INFO "Read %d characters from the character-mode device.\n", bytes_read);

	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off) {
	//sprintf(message, "%s(%zu letters)", buffer, len);
	size_of_message = strlen(message);
	
	printk(KERN_INFO "Wrote %zu characters to the character-mode device.\n", len);
	
	return len;
}

module_init(init_module);
module_exit(cleanup_module);