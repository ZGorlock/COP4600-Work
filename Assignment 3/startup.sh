sudo make
sudo insmod chardriverin.ko
sudo insmod chardriverout.ko
sudo mknod /dev/chardriverin c 247 0
sudo mknod /dev/chardriverout c 248 0
