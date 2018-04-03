#include "chardriver.h"


//Constants
#define DEVICE_NAME "chardriverin"


//Function Prototypes
int device_open(struct inode *inode, struct file *file);
int device_release(struct inode *inode, struct file *file);
ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset);
ssize_t device_write(struct file *file, const char *buff, size_t len, loff_t *off);


//Structs
static struct file_operations fops = {
	.write = device_write,
	.open = device_open,
	.release = device_release
};