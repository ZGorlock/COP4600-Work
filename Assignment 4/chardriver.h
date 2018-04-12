#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>


//Module Documentation
#define DRIVER_LICENSE "GPL"
#define DRIVER_AUTHOR "Group 1: Zack Gill, John Mac, Jacob Kerner"
#define DRIVER_DESC "A sample character-mode Linux device driver kernel module."
#define DRIVER_VER "0.1"


//Constants
#define SUCCESS 0
#define FAILURE -1
#define BUFFER_LENGTH 1024
#define TMP_BUFFER1_LENGTH 2048
#define TMP_BUFFER2_LENGTH 8192
