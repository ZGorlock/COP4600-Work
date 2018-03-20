#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>


//Module Documentation
#define DRIVER_LICENSE	"GPL"
#define DRIVER_AUTHOR 	"Group 1: Zack Gill, John McFarland, Jacob Kerner"
#define DRIVER_DESC   	"A sample character-mode Linux device driver kernel module."
#define DRIVER_VER		"0.1"


//Constants
#define DEVICE_NAME "charModeDevice"

#define SUCCESS 0
#define FAILURE -1

#define BUFFER_LENGTH 1024


//Function Prototypes
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);