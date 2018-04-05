#include "chardriverin.h"


MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VER);


static int Major;
static int isOpen = 0;

// Shared buffer
extern char * msg[BUFFER_LENGTH];

//static char msg[BUFFER_LENGTH] = {0};
static int msgSize;

EXPORT_SYMBOL(msg);
EXPORT_SYMBOL(msgSize);

static char newBuff[BUFFER_LENGTH];

// Declare and initialize the Mutex
static DEFINE_MUTEX(myMutex);

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
}

ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off) {

	// Start lock to prevent any data corruption or unauthorized usage
	mutex_lock(&myMutex);

	if (msgSize + len <= BUFFER_LENGTH) {
		strcat(msg, buff + *off);
		msgSize = strlen(msg);

	} else {
		printk(KERN_INFO "Error: %zu excess characters received in overflow\n", ((msgSize + len) - BUFFER_LENGTH)); // If len = 5, but only 2 can be stored, this prints 3.

		len = BUFFER_LENGTH - msgSize;

		memset(&newBuff[0], 0, sizeof(newBuff));
		strncpy(newBuff, buff + *off, len);

		strcat(msg, newBuff);
		msgSize = strlen(msg);
	}
	
	printk(KERN_INFO "Received %zu characters from the user\n", len);
	printk(KERN_INFO "Buffer (%d) [%s]\n", msgSize, msg);

	mutex_unlock(&myMutex);
	
	return len;
}
