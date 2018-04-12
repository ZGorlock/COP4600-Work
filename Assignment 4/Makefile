obj-m += chardriverin.o
obj-m += chardriverout.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	$(CC) testCharModeDriver.c -o test

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm test