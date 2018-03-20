#include "charModeDriver.h"


MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VER);


static int Major;
static int Device_Open = 0;

static char msg[BUFFER_LENGTH] = {0};
static int msgSize;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};


int init_module(void) {
	printk(KERN_INFO "Installing module.\n");

	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_ALERT "Failed to register character-mode device: %d\n", Major);
		return Major;
	}
	
	printk(KERN_INFO "Registered character-mode device with major number: %d\n", Major);
	
	return SUCCESS;
}

void cleanup_module(void) {
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_INFO "Unregistered character-mode device: %d\n", Major);
	
	printk(KERN_INFO "Removing module.\n");
}


int device_open(struct inode *inode, struct file *file) {
	static int counter = 0;
	
	if (Device_Open) {
		printk(KERN_WARNING "Attempted to open character-mode device but it is already open.\n");
		return -EBUSY;
	}
	
	Device_Open++;
	counter++;
	try_module_get(THIS_MODULE);
	printk(KERN_INFO "Opened character-mode device. Opened %d time(s).\n", counter);
	
	return SUCCESS;
}

int device_release(struct inode *inode, struct file *file) {
	if (!Device_Open) {
		printk(KERN_WARNING "Attempted to close character-mode device but it is not open.\n");
		return -EPERM;
	}
	
	Device_Open--;
	module_put(THIS_MODULE);
	printk(KERN_INFO "Closed character-mode device.\n");

	return SUCCESS;
}

ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	int error_count = 0;

	// copy_to_user has the format ( * to, *from, size) and returns 0 on success
	error_count = copy_to_user(buffer, msg, msgSize);

	if (error_count==0) {
		printk(KERN_INFO "EBBChar: Sent %d characters to the user\n", msgSize);
		return (msgSize=0);
	} else {
		printk(KERN_INFO "EBBChar: Failed to send %d characters to the user\n", error_count);
		return -EFAULT;
	}
}

ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
	sprintf(msg, "%s", buff);
	msgSize = strlen(msg);

	printk(KERN_INFO "EBBChar: Received %zu characters from the user\n", len);

	return len;
}
