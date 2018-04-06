#include "chardriverout.h"


MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VER);


static int Major;
static int isOpen = 0;

extern char msg[BUFFER_LENGTH] = {0};
static int msgSize;

static char newBuff[BUFFER_LENGTH];

struct mutex mutexLock;

/*
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};
*/

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
	
	if (isOpen == 1) {
		printk(KERN_WARNING "Attempted to open character-mode device but it is already open.\n");
		return -EBUSY;
	}
	
	isOpen = 1;
	counter++;
	try_module_get(THIS_MODULE);
	printk(KERN_INFO "Opened character-mode device. Opened %d time(s).\n", counter);
	
	return SUCCESS;
}

int device_release(struct inode *inode, struct file *file) {
	if (isOpen == 0) {
		printk(KERN_WARNING "Attempted to close character-mode device but it is not open.\n");
		return -EPERM;
	}
	
	isOpen = 0;
	module_put(THIS_MODULE);
	printk(KERN_INFO "Closed character-mode device.\n");

	return SUCCESS;
}

ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	int error_count = 0;
	mutex_init(&mutexLock);
	if(mutex_lock_interruptible(&mutexLock))
		return -ERESTARTSYS;

	if(length == 0){
		printk(KERN_INFO "Sent %d characters to the user\n", length);
		printk(KERN_INFO "Buffer (%d) [%s]\n", msgSize, msg);
		return SUCCESS;
	}

	if (length > msgSize) {
		length = msgSize;
	}
	
	// copy_to_user has the format ( * to, *from, size) and returns 0 on success
	error_count = copy_to_user(buffer, msg, length);

	if (error_count == 0) {
		printk(KERN_INFO "Sent %d characters to the user\n", length);

		memset(&newBuff[0], 0, sizeof(newBuff));
		memcpy(newBuff, msg + length, msgSize - length);
		memset(&msg[0], 0, sizeof(msg));
		memcpy(msg, newBuff, BUFFER_LENGTH);
		msgSize = strlen(msg);

		printk(KERN_INFO "Buffer (%d) [%s]\n", msgSize, msg);
		mutex_unlock(&mutexLock);
		return SUCCESS;
		
	} else {
		printk(KERN_INFO "Failed to send %d characters to the user\n", error_count);
		mutex_unlock(&mutexLock);
		return -EFAULT;
	}
}
/*
ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off) {

}*/

