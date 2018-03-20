#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


//Module Documentation
<<<<<<< HEAD
#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Group 1: Zack Gill, John Mac, Jacob Kerner"
#define DRIVER_DESC "A sample character-mode Linux device driver kernel module."
#define DRIVER_VER "0.1"
=======
#define DRIVER_LICENSE	"GPL"
#define DRIVER_AUTHOR 	"Group 1: Zack Gill, John McFarland, Jacob Kerner"
#define DRIVER_DESC   	"A sample character-mode Linux device driver kernel module."
#define DRIVER_VER		"0.1"
>>>>>>> origin/master


//Constants
#define DEVICE_NAME "charModeDevice"

#define SUCCESS 0
#define FAILURE -1

#define BUFFER_LENGTH 1024


//Function Prototypes
int device_open(struct inode *inode, struct file *file);
int device_release(struct inode *inode, struct file *file);
ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset);
ssize_t device_write(struct file *file, const char *buff, size_t len, loff_t *off);