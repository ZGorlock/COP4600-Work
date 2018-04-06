sudo make
sudo insmod chardriverin.ko
sudo insmod chardriverout.ko
sudo mknod /dev/chardriverin c 245 0
sudo mknod /dev/chardriverout c 246 0
